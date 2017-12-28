#include "Image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>


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
