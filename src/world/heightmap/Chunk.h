#pragma once

#include "../../math/Vec3.h"

struct TileData
{
    float height;
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    inline Vec3f getColor() const { return Vec3f(red, green, blue) / 255.0f; }
    inline void setColor(const Vec3f& color)
    {
        red = static_cast<unsigned char>(color.x * 255.0f);
        green = static_cast<unsigned char>(color.y * 255.0f);
        blue = static_cast<unsigned char>(color.z * 255.0f);
    }
};

template<unsigned int size>
class Chunk
{
public:
    inline Chunk() {  }
    inline ~Chunk() {  }

    inline float getHeightAt(unsigned int x, unsigned int z) const { return m_data[x + z * size].height; }
    inline void setHeightAt(unsigned int x, unsigned int z, float height) { m_data[x + z * size].height = height; }

    inline Vec3f getColorAt(unsigned int x, unsigned int z) const { return m_data[x + z * size].getColor(); }
    inline void setColorAt(unsigned int x, unsigned int z, const Vec3f& color) { m_data[x + z * size].setColor(color); }
private:
    TileData m_data[size * size];
};
