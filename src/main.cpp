#include <iostream>

#include "graphics/RayTracer.h"
#include "graphics/effect/VignetteEffect.h"
#include "graphics/effect/NoiseDitheringEffect.h"
#include "world/World.h"

#include <string>

int main(int argc, char** argv)
{
    HDRImage image(1920, 1080);
    float aspectRatio = static_cast<float>(image.getWidth()) / static_cast<float>(image.getHeight());
    Camera<float> camera(Vec3f(1.0f, 32.0f, 1.0f), 45.0f, -10.0f, 90.0f / aspectRatio, aspectRatio);

    World world(8, 8, 10);

    RayTracer rayTracer;
    rayTracer.traceFullImage(image, camera, &world);

    VignetteEffect vignette;
    //vignette.apply(image);

    NoiseDitheringEffect noiseDithering;
    noiseDithering.apply(image);

    RGBImage result(image.getWidth(), image.getHeight());
    image.toRGBImage(result);

    result.writeToJPEG("Preview.jpg", 100);

    return 0;
}
