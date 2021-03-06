#include "World.h"

#include "heightmap/HeightmapGenerator.h"

#define CLAMP(x, min, max) (x < min ? min : (x > max ? max : x))

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
        if (m_water.isInWater(currentPosition)) {
            // Don't calculate reflections if it isn't necessary
            if (parameter.intersectionOnly) {
                result.intersects = true;
                return result;
            }

            // Trace reflected ray
            result = trace(m_water.reflectRay(currentPosition, ray.direction), parameter);

            result.distance += distance;

            // Absorb light
            result.color = m_water.reflectColor(result.color);

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
                Vec3f diffuseColor(0.4f);
                Vec3f normal = m_heightmap.getNormalInterpolated(currentPosition.x, currentPosition.z);
                float angle = normal.dot(lightDirection * -1.0f);

                // Shadow
                if (angle > 0.0f && inShadow(Vec3f(currentPosition.x, height, currentPosition.z))) {
                    angle = -1.0f;
                }
                float light = angle > 0.0f ? (angle > 0.3f ? (angle > 0.6f ? 1.0f : 0.66f) : 0.33f) : 0.0f;
                // float light = CLAMP(angle * 8.0f, 0.0f, 1.0f);
                light = light * 0.25f + 0.25f;

                diffuseColor *= light;

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

bool World::inShadow(const Vec3f& point) const
{
    Vec3f lightDirection = m_sky.getLightDirection();
    TraceParamter shadowParameter;
    shadowParameter.intersectionOnly = true;
    TraceResult shadowResult = trace(Rayf(point, lightDirection * -1.0f), shadowParameter);
    return shadowResult.intersects;
}
