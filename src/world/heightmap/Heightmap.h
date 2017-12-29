#pragma once

#include <vector>

#include "Chunk.h"
#include "../../graphics/RayTracable.h"

static const unsigned int CHUNK_SIZE = 64;

class Heightmap
{
    friend class HeightmapGenerator;
public:
    Heightmap(unsigned int width, unsigned int length);
    ~Heightmap();

    float getHeightAt(unsigned int x, unsigned int z) const;
    float getHeightInterpolated(float x, float z) const;
    Vec3f getNormalAt(float x, float z) const;

    inline unsigned int getGridWidth() const { return m_width * CHUNK_SIZE; }
    inline unsigned int getGridLength() const { return m_length * CHUNK_SIZE; }

    inline bool inBounds(float x, float z) const { return x >= 0.0f && z >= 0.0f && x <= getGridWidth() - 1 && z <= getGridLength() - 1; }
private:
    inline Chunk<CHUNK_SIZE>* getChunkAt(unsigned int x, unsigned int z) { return m_chunks[x + z * m_width]; }
    inline const Chunk<CHUNK_SIZE>* getChunkAt(unsigned int x, unsigned int z) const { return m_chunks[x + z * m_width]; }

    unsigned int m_width;
    unsigned int m_length;
    std::vector<Chunk<CHUNK_SIZE>*> m_chunks;
};
