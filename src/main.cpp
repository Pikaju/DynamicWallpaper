#include <iostream>

#include "graphics/RayTracer.h"
#include "world/World.h"

int main(int argc, char** argv)
{
    RGBImage image(1920, 1080);
    float aspectRatio = static_cast<float>(image.getWidth()) / static_cast<float>(image.getHeight());
    Camera<float> camera(Vec3f(0.0f, 32.0f, 0.0f), 45.0f, -10.0f, 90.0f / aspectRatio, aspectRatio);

    World world(8, 8);

    RayTracer rayTracer;
    rayTracer.traceFullImage(image, camera, &world);

    image.writeToJPEG("Preview.jpg", 100);

    return 0;
}
