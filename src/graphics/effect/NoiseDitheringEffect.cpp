#include "NoiseDitheringEffect.h"

#include <functional>

void NoiseDitheringEffect::apply(RGBImage& image) const
{
    for (unsigned int x = 0; x < image.getWidth(); x++) {
        for (unsigned int y = 0; y < image.getHeight(); y++) {
            std::hash<unsigned int> hasher;
            int hash = hasher(x) ^ hasher(y + image.getWidth());
            int red = (hasher(hash + 0) & 1) + image.getRed(x, y);
            int green = (hasher(hash + 1) & 1) + image.getGreen(x, y);
            int blue = (hasher(hash + 2) & 1) + image.getBlue(x, y);
            image.setRed(x, y, std::min(red, 255));
            image.setGreen(x, y, std::min(green, 255));
            image.setBlue(x, y, std::min(blue, 255));
        }
    }
}
