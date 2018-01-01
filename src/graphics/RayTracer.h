#pragma once

#include "RayTracable.h"
#include "../util/Image.h"
#include "../math/Camera.h"

class RayTracer
{
public:
    RayTracer();
    ~RayTracer();

    /** Ray trace every pixel in an entire image.
     *  @param image The image to fill with ray tracing results.
     *  @param camera The camera that shoots out rays to trace.
     *  @param object The object that the ray tracing should be calculated on.
     */
    void traceFullImage(HDRImage& image, Camera<float>& camera, const RayTracable* object) const;
private:
    Vec3f traceRay(const Rayf& ray, const RayTracable* object) const;
};
