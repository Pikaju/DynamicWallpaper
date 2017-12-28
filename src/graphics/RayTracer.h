#pragma once

#include "RayTracable.h"
#include "../util/Image.h"
#include "../math/Camera.h"

class RayTracer
{
public:
    RayTracer();
    ~RayTracer();

    void traceFullImage(RGBImage& image, Camera<float>& camera, const RayTracable* object) const;
private:
    unsigned int traceRay(const Rayf& ray, const RayTracable* object) const;
};
