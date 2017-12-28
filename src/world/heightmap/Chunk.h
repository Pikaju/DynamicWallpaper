#pragma once

template<unsigned int size>
class Chunk
{
public:
    inline Chunk() {  }
    inline ~Chunk() {  }

    inline float getHeightAt(unsigned int x, unsigned int z) const { return m_heightmap[x + z * size]; }
    inline void setHeightAt(unsigned int x, unsigned int z, float height) { m_heightmap[x + z * size] = height; }
private:
    float m_heightmap[size * size];
};
