#pragma once

#include "../../util/Image.h"

class VignetteEffect
{
public:
    /** Add the vignette to an image.
     *  @param image The image to apply a vignette to.
     */
    void apply(HDRImage& image) const;
};
