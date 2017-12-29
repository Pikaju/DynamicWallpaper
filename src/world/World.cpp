#include "World.h"

#include "heightmap/HeightmapGenerator.h"

World::World(unsigned int width, unsigned int length) : m_heightmap(width, length), m_sky(), m_fog(), m_water(-20.0f)
{
    HeightmapGenerator::generate(m_heightmap);
}

World::~World()
{
}

#include <iostream>

TraceResult World::trace(const Rayf& ray, const TraceParamter& parameter) const
{
    TraceResult result;

    const float STEP = 0.5f;
    const float MAX_SLOPE = 1.7f;
    const float ZNEAR = 0.0f;

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
            result.color = (result.color + Vec3f(0.2f, 0.3f, 0.4f)) * Vec3f(0.5f);

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
                Vec3f lightDirection = Vec3f(-0.8f, -0.5f, 0.2f).normalized();
                Vec3f diffuseColor(0.1, 0.08f, 0.03f);
                Vec3f normal = m_heightmap.getNormalAt(currentPosition.x, currentPosition.z);
                float angle = normal.dot(lightDirection * -1.0f);
                //diffuseColor *= std::max(angle, 0.0f) * 0.75f + 0.25f;
                //diffuseColor *= angle > 0.0f ? 1.0f : 0.5f;

                // Shadow
                diffuseColor *= getShadowMultiplier(Vec3f(currentPosition.x, height, currentPosition.z));

                // Apply fog
                result.color = m_fog.applyFog(diffuseColor, m_sky, ray.origin, currentPosition);
                return result;
            }
        }

        // Set step multiplier based on distance to surface for performance increase
        stepMultiplier = (currentPosition.y - std::max(height, m_water.getHeight())) / MAX_SLOPE + 0.125f;
    }
    result.intersects = false;
    result.color = m_sky.getColor();
    return result;
}

bool World::inShadow(const Vec3f& position) const
{
    Vec3f lightDirection = Vec3f(-0.8f, -0.5f, 0.2f).normalized();
    TraceParamter shadowParameter;
    shadowParameter.intersectionOnly = true;
    TraceResult shadowResult = trace(Rayf(position, lightDirection * -1.0f), shadowParameter);
    return shadowResult.intersects;
}
