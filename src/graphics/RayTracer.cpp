#include "RayTracer.h"

#include <iostream>
#include <algorithm>

#define CLAMP(x, min, max) (x < min ? min : (x > max ? max : x))

RayTracer::RayTracer()
{
}

RayTracer::~RayTracer()
{
}

void RayTracer::traceFullImage(HDRImage& image, Camera<float>& camera, const RayTracable* object) const
{
    for (unsigned int x = 0; x < image.getWidth(); x++) {
        for (unsigned int y = 0; y < image.getHeight(); y++) {
            float dx = static_cast<float>(x) / static_cast<float>(image.getWidth() - 1) * 2.0f - 1.0f;
            float dy = -(static_cast<float>(y) / static_cast<float>(image.getHeight() - 1) * 2.0f - 1.0f);

            Rayf ray = camera.getViewRay(dx, dy);
            image.setRGB(x, y, traceRay(ray, object));
        }
    }
}

Vec3f RayTracer::traceRay(const Rayf& ray, const RayTracable* object) const
{
    TraceParamter parameter;
    TraceResult result = object->trace(ray, parameter);
    return result.color;
}
