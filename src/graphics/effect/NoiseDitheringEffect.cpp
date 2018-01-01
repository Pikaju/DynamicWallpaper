#include "NoiseDitheringEffect.h"

#include <functional>

void NoiseDitheringEffect::apply(HDRImage& image) const
{
    for (unsigned int x = 0; x < image.getWidth(); x++) {
        for (unsigned int y = 0; y < image.getHeight(); y++) {
            std::hash<unsigned int> hasher;
            int hash = hasher(x) ^ hasher(y + image.getWidth());
            float red = (hasher(hash + 0) & 1) / 255.0f + image.getRed(x, y);
            float green = (hasher(hash + 1) & 1) / 255.0f + image.getGreen(x, y);
            float blue = (hasher(hash + 2) & 1) / 255.0f + image.getBlue(x, y);
            image.setRed(x, y, red);
            image.setGreen(x, y, green);
            image.setBlue(x, y, blue);
        }
    }
}
