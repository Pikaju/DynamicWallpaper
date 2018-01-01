#include "Image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

#define CLAMP(x, min, max) (x < min ? min : (x > max ? max : x))

RGBImage::RGBImage(unsigned int width, unsigned int height) : m_width(width), m_height(height), m_pixels(width * height * 3)
{
}

RGBImage::~RGBImage()
{
}

void RGBImage::writeToJPEG(const char* file, int quality) const
{
    stbi_write_jpg(file, m_width, m_height, 3, reinterpret_cast<const float*>(m_pixels.data()), quality);
}

HDRImage::HDRImage(unsigned int width, unsigned int height) : m_width(width), m_height(height), m_pixels(width * height * 3)
{
}

HDRImage::~HDRImage()
{
}

void HDRImage::toRGBImage(RGBImage& image) const
{
    for (unsigned int x = 0; x < getWidth(); x++) {
        for (unsigned int y = 0; y < getHeight(); y++) {
            image.setRed(x, y, static_cast<unsigned char>(CLAMP(getRed(x, y), 0.0f, 1.0f) * 255.0f));
            image.setGreen(x, y, static_cast<unsigned char>(CLAMP(getGreen(x, y), 0.0f, 1.0f) * 255.0f));
            image.setBlue(x, y, static_cast<unsigned char>(CLAMP(getBlue(x, y), 0.0f, 1.0f) * 255.0f));
        }
    }
}
