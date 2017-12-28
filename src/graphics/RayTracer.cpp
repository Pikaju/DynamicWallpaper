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
            Vec3f color = traceRay(ray, object);
            image.setRed(x, y, static_cast<unsigned char>(color.x * 255.0f));
            image.setGreen(x, y, static_cast<unsigned char>(color.y * 255.0f));
            image.setBlue(x, y, static_cast<unsigned char>(color.z * 255.0f));
        }
    }
}

Vec3f RayTracer::traceRay(const Rayf& ray, const RayTracable* object) const
{
    TraceResult result = object->trace(ray);
    Vec3f sky(0.2f, 0.8f, 0.7f);
    return result.intersects ? Vec3f((result.distance / 512.0f)) * sky : sky;
}
