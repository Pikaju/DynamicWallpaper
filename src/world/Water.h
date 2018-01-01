#pragma once

#include "../math/Ray.h"

class Water
{
public:
    Water(float height);
    ~Water();

    Rayf reflectRay(const Vec3f& position, const Vec3f& direction) const;
    Vec3f reflectColor(const Vec3f& color) const;

    inline bool isInWater(const Vec3f point) const { return point.y < getHeight(); }
    inline float getHeight() const { return m_height; }
private:
    float m_height;
};
