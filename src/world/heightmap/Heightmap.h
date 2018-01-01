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

    /**
     *  @param x The x-coordinate that should be checked, must be between 0 and width - 1.
     *  @param z The z-coordinate that should be checked, must be between 0 and length - 1.
     *  @return The height of the heightmap at a specific coordinate.
     */
    float getHeightAt(unsigned int x, unsigned int z) const;

    /** Linearly interpolates the height of the grid at a specific coordinate.
     *  @param x The x-coordinate that should be checked.
     *  @param z The z-coordinate that should be checked.
     *  @return The height of the heightmap, or 0.0 if it is out of bounds.
     */
    float getHeightInterpolated(float x, float z) const;

    /** Linear interpolates the normal of the heightmap's surface at a specific coordinate.
     *  @param x The x-coordinate that should be checked.
     *  @param z The z-coordinate that should be checked.
     *  @return The normal of the heightmap's surface, likely pointing straight up if the coordinate if out of bounds.
     */
    Vec3f getNormalInterpolated(float x, float z) const;

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
