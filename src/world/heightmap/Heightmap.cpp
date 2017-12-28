#include "Heightmap.h"

#include <math.h>

#define LERP(a, b, x) (a + (b - a) * x)

Heightmap::Heightmap(unsigned int width, unsigned int length) : m_width(width), m_length(length), m_chunks(width * length)
{
    for (size_t i = 0; i < m_chunks.size(); i++) {
        m_chunks[i] = new Chunk<CHUNK_SIZE>();
    }
}

Heightmap::~Heightmap()
{
    for (size_t i = 0; i < m_chunks.size(); i++) {
        delete m_chunks[i];
    }
}

TraceResult Heightmap::trace(const Rayf& ray) const
{
    TraceResult result;

    const float STEP = 1.0f;
    const float MAX_SLOPE = 1.7f;
    const float WATER_HEIGHT = -20.0f;

    float stepMultiplier = 1.0f;

    for (float distance = 0.0f; ; distance += STEP * stepMultiplier) {
        Vec3f currentPosition = ray.march(distance);

        if (currentPosition.x < 0.0f || currentPosition.z < 0.0f || currentPosition.x > getGridWidth() - 1 || currentPosition.z > getGridLength() - 1) {
            break;
        }

        // Water surface
        if (currentPosition.y < WATER_HEIGHT) {
            Rayf reflectedRay(currentPosition, ray.direction * Vec3f(1.0f, -1.0f, 1.0f));
            reflectedRay.origin.y = WATER_HEIGHT;
            result = trace(reflectedRay);
            result.distance += distance;
            result.diffuseColor = result.diffuseColor * Vec3f(0.25f) + Vec3f(0.1f, 0.2f, 0.2f);
            return result;
        }

        // Check with the nearest neighbor if intersection is possible
        float height = getHeightAt(static_cast<unsigned int>(currentPosition.x), static_cast<unsigned int>(currentPosition.z));
        if (currentPosition.y - height < MAX_SLOPE) {
            // Check for intersection with bilinear interpolation
            height = getHeightInterpolated(currentPosition.x, currentPosition.z);
            if (currentPosition.y <= height) {
                result.intersects = true;
                result.distance = distance;
                result.diffuseColor = Vec3f(0.1f, 0.1f, 0.1f);
                return result;
            }
        }

        // Set step multiplier based on distance to surface for performance increase
        stepMultiplier = (currentPosition.y - std::max(height, WATER_HEIGHT)) / MAX_SLOPE + 0.125f;
    }
    result.intersects = false;
    return result;
}

float Heightmap::getHeightAt(unsigned int x, unsigned int z) const
{
    const Chunk<CHUNK_SIZE>* chunk = getChunkAt(x / CHUNK_SIZE, z / CHUNK_SIZE);
    return chunk->getHeightAt(x % CHUNK_SIZE, z % CHUNK_SIZE);
}

float Heightmap::getHeightInterpolated(float x, float z) const
{
    if (x < 0.0f || z < 0.0f || x > getGridWidth() - 1 || z > getGridLength() - 1) {
        return 0.0f;
    }
    float h00 = getHeightAt(static_cast<unsigned int>(floor(x)), static_cast<unsigned int>(floor(z)));
    float h01 = getHeightAt(static_cast<unsigned int>(floor(x)), static_cast<unsigned int>(ceil(z)));
    float h10 = getHeightAt(static_cast<unsigned int>(ceil(x)), static_cast<unsigned int>(floor(z)));
    float h11 = getHeightAt(static_cast<unsigned int>(ceil(x)), static_cast<unsigned int>(ceil(z)));
    float fx = x - floor(x);
    float fz = z - floor(z);
    return LERP(LERP(h00, h10, fx), LERP(h01, h11, fx), fz);
}
