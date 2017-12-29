#include "World.h"

#include "heightmap/HeightmapGenerator.h"

#define LERP(a, b, x) (a + (b - a) * x)

World::World(unsigned int width, unsigned int length) : m_heightmap(width, length), m_sky(), m_water(-20.0f)
{
    HeightmapGenerator::generate(m_heightmap);
}

World::~World()
{
}

TraceResult World::trace(const Rayf& ray) const
{
    TraceResult result;

    const float STEP = 1.0f;
    const float MAX_SLOPE = 1.7f;

    float stepMultiplier = 1.0f;

    for (float distance = 0.0f; ; distance += STEP * stepMultiplier) {
        Vec3f currentPosition = ray.march(distance);

        if (!m_heightmap.inBounds(currentPosition.x, currentPosition.z)) {
            break;
        }

        // Water surface
        if (currentPosition.y < m_water.getHeight()) {
            Rayf reflectedRay(currentPosition, ray.direction * Vec3f(1.0f, -1.0f, 1.0f));
            reflectedRay.origin.y = m_water.getHeight();
            result = trace(reflectedRay);
            result.distance += distance;
            result.color = (result.color + Vec3f(0.2f, 0.4f, 0.6f)) * Vec3f(0.3f);
            result.color = LERP(result.color, m_sky.getColor(), distance / (sqrt(512.0f * 512.0f * 2.0f)));
            return result;
        }

        // Check with the nearest neighbor if intersection is possible
        float height = m_heightmap.getHeightAt(static_cast<unsigned int>(currentPosition.x), static_cast<unsigned int>(currentPosition.z));
        if (currentPosition.y - height < MAX_SLOPE) {
            // Check for intersection with bilinear interpolation
            height = m_heightmap.getHeightInterpolated(currentPosition.x, currentPosition.z);
            if (currentPosition.y <= height) {
                result.intersects = true;
                result.distance = distance;
                result.color = LERP(Vec3f(0.1f, 0.1f, 0.1f), m_sky.getColor(), result.distance / (sqrt(512.0f * 512.0f * 2.0f)));
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
