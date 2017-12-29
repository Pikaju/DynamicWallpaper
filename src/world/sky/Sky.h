#pragma once

#include "../../math/Vec3.h"

class Sky
{
public:
    Sky();
    ~Sky();

    Vec3f getColor(const Vec3f& direction) const;
    Vec3f getColor() const;
    inline Vec3f getLightDirection() const { return Vec3f(-0.8f, -0.15f, -0.4f).normalized(); }
};
