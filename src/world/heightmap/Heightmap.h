#pragma once

#include <vector>

#include "Chunk.h"

static const unsigned int CHUNK_SIZE = 64;

class Heightmap
{
public:
    Heightmap(unsigned int width, unsigned int length);
    ~Heightmap();

    float getHeightAt(unsigned int x, unsigned int z) const;
    float getHeightInterpolated(float x, float z) const;

    inline unsigned int getGridWidth() const { return m_width * CHUNK_SIZE; }
    inline unsigned int getGridLength() const { return m_length * CHUNK_SIZE; }
private:
    inline const Chunk<CHUNK_SIZE>* getChunkAt(unsigned int x, unsigned int z) const { return m_chunks[x + z * m_length]; }

    unsigned int m_width;
    unsigned int m_length;
    std::vector<Chunk<CHUNK_SIZE>*> m_chunks;
};
