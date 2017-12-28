#include <iostream>

#include "graphics/RayTracer.h"
#include "graphics/Sphere.h"

int main(int argc, char** argv)
{
    RGBImage image(720, 480);
    Camera<float> camera(Vec3f(), 70.0f, static_cast<float>(image.getWidth()) / static_cast<float>(image.getHeight()));
    Sphere sphere(Vec3f(0.2f, 0.1f, 4.0f), 1.0f);

    RayTracer rayTracer;
    rayTracer.traceFullImage(image, camera, &sphere);

    image.writeToJPEG("Preview.jpg", 100);

    return 0;
}
