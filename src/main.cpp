#include <iostream>

#include "graphics/RayTracer.h"
#include "world/World.h"

#include <string>

int main(int argc, char** argv)
{
    RGBImage image(1280, 720);
    float aspectRatio = static_cast<float>(image.getWidth()) / static_cast<float>(image.getHeight());
    Camera<float> camera(Vec3f(1.0f, 32.0f, 1.0f), 45.0f, -10.0f, 90.0f / aspectRatio, aspectRatio);

    for (unsigned int i = 10; i < 64; i++) {
        World world(8, 8, i);

        RayTracer rayTracer;
        rayTracer.traceFullImage(image, camera, &world);

        image.writeToJPEG(("./examples/Preview" + std::to_string(i) + ".jpg").c_str(), 90);
    }

    return 0;
}
