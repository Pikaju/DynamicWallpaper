#include <iostream>

#include "graphics/RayTracer.h"
#include "world/heightmap/HeightmapGenerator.h"

int main(int argc, char** argv)
{
    RGBImage image(1280, 720);
    float aspectRatio = static_cast<float>(image.getWidth()) / static_cast<float>(image.getHeight());
    Camera<float> camera(Vec3f(0.0f, 32.0f, 0.0f), 45.0f, -10.0f, 90.0f / aspectRatio, aspectRatio);

    Heightmap heightmap(8, 8);
    HeightmapGenerator::generate(heightmap);

    RayTracer rayTracer;
    rayTracer.traceFullImage(image, camera, &heightmap);

    image.writeToJPEG("Preview.jpg", 100);

    return 0;
}
