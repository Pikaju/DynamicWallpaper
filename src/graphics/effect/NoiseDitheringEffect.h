#pragma once

#include "../../util/Image.h"

class NoiseDitheringEffect
{
public:
    /** Apply noise based dithering to an image
     *  @param image The image to apply dithering to.
     */
    void apply(HDRImage& image) const;
};
