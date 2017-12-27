#pragma once

#include "../math/Vec3.h"

class Raytracer
{
public:
    Raytracer();
    ~Raytracer();
private:
    void traceDirection(const Vec3& direction);
};
