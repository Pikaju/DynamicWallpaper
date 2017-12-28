#pragma once

#include "../math/Ray.h"

struct TraceResult
{
    bool intersects;
    float distance;
};

class RayTracable
{
public:
    inline RayTracable() {  }
    virtual inline ~RayTracable() {  }

    virtual TraceResult trace(const Rayf& ray) const = 0;
};
