#pragma once

#include "../math/Vec3.h"

class Sky;

class Fog
{
public:
    Fog();
    ~Fog();

    Vec3f applyFog(const Vec3f& color, const Sky& sky, const Vec3f& p0, const Vec3f& p1) const;
private:
    float fogAntiderivative(float height) const;
};
