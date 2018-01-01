#pragma once

#include "RayTracable.h"
#include "../util/Image.h"
#include "../math/Camera.h"

class RayTracer
{
public:
    RayTracer();
    ~RayTracer();

    void traceFullImage(HDRImage& image, Camera<float>& camera, const RayTracable* object) const;
private:
    Vec3f traceRay(const Rayf& ray, const RayTracable* object) const;
};
