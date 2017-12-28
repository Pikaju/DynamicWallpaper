#pragma once

#include <vector>

class RGBImage
{
public:
    RGBImage(unsigned int width, unsigned int height);
    ~RGBImage();

    void writeToJPEG(const char* file, int quality) const;

    inline unsigned char getRed(unsigned int x, unsigned int y) const { return m_pixels[(x + y * m_width) * 3 + 0]; }
    inline unsigned char getGreen(unsigned int x, unsigned int y) const { return m_pixels[(x + y * m_width) * 3 + 1]; }
    inline unsigned char getBlue(unsigned int x, unsigned int y) const { return m_pixels[(x + y * m_width) * 3 + 2]; }

    inline void setRed(unsigned int x, unsigned int y, unsigned char value) { m_pixels[(x + y * m_width) * 3 + 0] = value; }
    inline void setGreen(unsigned int x, unsigned int y, unsigned char value) { m_pixels[(x + y * m_width) * 3 + 1] = value; }
    inline void setBlue(unsigned int x, unsigned int y, unsigned char value) { m_pixels[(x + y * m_width) * 3 + 2] = value; }

    inline unsigned int getRGB(unsigned int x, unsigned int y) const
    {
        return (static_cast<unsigned int>(getRed(x, y)) << 16) | (static_cast<unsigned int>(getGreen(x, y)) << 8) | (static_cast<unsigned int>(getBlue(x, y)) << 0);
    }

    inline void setRGB(unsigned int x, unsigned int y, unsigned int rgb)
    {
        setRed(x, y, static_cast<unsigned char>((rgb >> 16) & 0xff));
        setGreen(x, y, static_cast<unsigned char>((rgb >> 8) & 0xff));
        setBlue(x, y, static_cast<unsigned char>(rgb & 0xff));
    }

    inline unsigned int getWidth() const { return m_width; }
    inline unsigned int getHeight() const { return m_height; }
private:
    unsigned int m_width;
    unsigned int m_height;
    std::vector<unsigned char> m_pixels;
};
