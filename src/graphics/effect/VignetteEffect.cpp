#include "VignetteEffect.h"

#include <math.h>

#define CLAMP(x, min, max) (x < min ? min : (x > max ? max : x))

void VignetteEffect::apply(RGBImage& image) const
{
    for (unsigned int x = 0; x < image.getWidth(); x++) {
        for (unsigned int y = 0; y < image.getHeight(); y++) {
            float dx = static_cast<float>(x) / static_cast<float>(image.getWidth() - 1) * 2.0f - 1.0f;
            float dy = -(static_cast<float>(y) / static_cast<float>(image.getHeight() - 1) * 2.0f - 1.0f);
            float distance = sqrt(dx * dx + dy * dy);
            float multiplier = CLAMP(1.0f - pow(0.25f, 1.5f - distance) * 0.8f, 0.0f, 1.0f);

            image.setRed(x, y, static_cast<unsigned char>(image.getRed(x, y) * multiplier));
            image.setGreen(x, y, static_cast<unsigned char>(image.getGreen(x, y) * multiplier));
            image.setBlue(x, y, static_cast<unsigned char>(image.getBlue(x, y) * multiplier));
        }
    }
}
