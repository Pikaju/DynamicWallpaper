#pragma once

#include "../math/Vec3.h"

class RayTracer
{
public:
    RayTracer();
    ~RayTracer();
private:
    void traceDirection(const Vec3& direction);
};
