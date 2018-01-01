#include "World.h"

#include "heightmap/HeightmapGenerator.h"

World::World(unsigned int width, unsigned int length, unsigned int seed) : m_heightmap(width, length), m_sky(), m_fog(), m_water(-20.0f)
{
    HeightmapGenerator::generate(m_heightmap, seed);
}

World::~World()
{
}

TraceResult World::trace(const Rayf& ray, const TraceParamter& parameter) const
{
    TraceResult result;

    const float STEP = 0.5f;
    const float MAX_SLOPE = 1.7f;
    const float ZNEAR = 0.125f;

    float stepMultiplier = 1.0f;

    for (float distance = ZNEAR; ; distance += STEP * stepMultiplier) {
        Vec3f currentPosition = ray.march(distance);

        if (!m_heightmap.inBounds(currentPosition.x, currentPosition.z)) {
            break;
        }

        // Water surface
        if (currentPosition.y < m_water.getHeight()) {
            if (parameter.intersectionOnly) {
                result.intersects = true;
                return result;
            }

            // Trace reflected ray
            Rayf reflectedRay(currentPosition, ray.direction * Vec3f(1.0f, -1.0f, 1.0f));
            reflectedRay.origin.y = m_water.getHeight();
            result = trace(reflectedRay, parameter);

            result.distance += distance;

            // Absorb light
            result.color = (result.color + Vec3f(0.2f, 0.3f, 0.4f) * 0.4f) * Vec3f(0.6f);

            // Apply fog
            result.color = m_fog.applyFog(result.color, m_sky, ray.origin, currentPosition);
            return result;
        }

        // Check with the nearest neighbor if intersection is possible
        float height = m_heightmap.getHeightAt(static_cast<unsigned int>(currentPosition.x), static_cast<unsigned int>(currentPosition.z));
        if (currentPosition.y - height < MAX_SLOPE) {
            // Check for intersection with bilinear interpolation
            height = m_heightmap.getHeightInterpolated(currentPosition.x, currentPosition.z);
            if (currentPosition.y < height) {
                result.intersects = true;
                if (parameter.intersectionOnly) return result;

                result.distance = distance;

                // Lighting
                Vec3f lightDirection = m_sky.getLightDirection();
                Vec3f diffuseColor = m_heightmap.getColorAt(static_cast<unsigned int>(currentPosition.x), static_cast<unsigned int>(currentPosition.z));
                //if (height > 16.0f) diffuseColor = Vec3f(1.0f);
                Vec3f normal = m_heightmap.getNormalInterpolated(currentPosition.x, currentPosition.z);
                float angle = normal.dot(lightDirection * -1.0f);
                //diffuseColor *= std::max(angle, 0.0f) * 0.75f + 0.25f;
                
                // Shadow
                if (angle > 0.0f && inShadow(Vec3f(currentPosition.x, height, currentPosition.z))) {
                    angle = -1.0f;
                }
                float light = angle > 0.0f ? (angle > 0.3f ? (angle > 0.6f ? 1.0f : 0.66f) : 0.33f) : 0.0f;
                light = light * 0.25f + 0.75f;

                diffuseColor *= light;
                diffuseColor *= 0.6f;

                // Apply fog
                result.color = m_fog.applyFog(diffuseColor, m_sky, ray.origin, currentPosition);
                return result;
            }
        }

        // Set step multiplier based on distance to surface for performance increase
        stepMultiplier = (currentPosition.y - std::max(height, m_water.getHeight())) / MAX_SLOPE + 0.125f;
    }
    result.intersects = false;
    result.color = m_sky.getColor(ray.direction);
    return result;
}

bool World::inShadow(const Vec3f& position) const
{
    Vec3f lightDirection = m_sky.getLightDirection();
    TraceParamter shadowParameter;
    shadowParameter.intersectionOnly = true;
    TraceResult shadowResult = trace(Rayf(position, lightDirection * -1.0f), shadowParameter);
    return shadowResult.intersects;
}
