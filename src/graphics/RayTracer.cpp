#include "RayTracer.h"

#include <iostream>

RayTracer::RayTracer()
{
}

RayTracer::~RayTracer()
{
}

void RayTracer::traceFullImage(RGBImage& image, Camera<float>& camera, const RayTracable* object) const
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

unsigned int RayTracer::traceRay(const Rayf& ray, const RayTracable* object) const
{
    return object->trace(ray).intersects ? 0x20a090 : 0;
}
