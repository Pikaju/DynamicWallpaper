#pragma once

#include "../math/Ray.h"

struct TraceResult
{
    bool intersects;
    float distance;
    Vec3f color;
};

class RayTracable
{
public:
    inline RayTracable() {  }
    virtual inline ~RayTracable() {  }

    virtual TraceResult trace(const Rayf& ray) const = 0;
};
