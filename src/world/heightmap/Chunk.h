#pragma once

template<unsigned int size>
class Chunk
{
public:
    inline Chunk() {  }
    inline ~Chunk() {  }

    inline float getHeightAt(unsigned int x, unsigned int z) const { return m_data[x + z * size].height; }
    inline void setHeightAt(unsigned int x, unsigned int z, float height) { m_data[x + z * size].height = height; }
private:
    float m_data[size * size];
};
