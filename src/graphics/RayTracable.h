#pragma once

#include "../math/Ray.h"

struct TraceParamter
{
    bool intersectionOnly = false;
};

struct TraceResult
{
    /** Whether the object was intersected by the ray or not. */
    bool intersects = false;

    /** At what distance from the ray's origin the object was intersected. */
    float distance = -1.0f;

    /** What color the light would likely have, if it came from the other direction. */
    Vec3f color = Vec3f(0.0f);
};

class RayTracable
{
public:
    inline RayTracable() {  }
    virtual inline ~RayTracable() {  }

    /** Traces one ray of light.
     *  This is done in the opposite direction, essentially starting from the camera,
     *  instead of the light source, for easier calculations and faster rendering times.
     *  @param ray The ray of light to trace.
     *  @param parameter An extra parameter to change the way the light is traced.
     *  @return A TraceResult object containing relevant information about the object, when tracing the specific ray.
     */
    virtual TraceResult trace(const Rayf& ray, const TraceParamter& parameter) const = 0;
};
