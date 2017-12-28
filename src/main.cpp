#include <iostream>

#include "math/Vec3.h"
#include "math/Ray.h"

#include <FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD.h>

#include "util/Image.h"

int main(int argc, char** argv)
{
    FastNoiseSIMD* myNoise = FastNoiseSIMD::NewFastNoiseSIMD();

    // Get a set of 16 x 16 x 16 Simplex Fractal noise
    float* noiseSet = myNoise->GetSimplexFractalSet(0, 0, 0, 256, 256, 1, 1.5f);
    int index = 0;

    RGBImage image(256, 256);

    for (int x = 0; x < image.getWidth(); x++)
    {
        for (int y = 0; y < image.getHeight(); y++)
        {
            for (int z = 0; z < 1; z++)
            {
                std::cout << noiseSet[index++] << std::endl;
                image.setRed(x, y, noiseSet[index] * 127 + 128);
                image.setGreen(x, y, noiseSet[index] * 127 + 128);
                image.setBlue(x, y, noiseSet[index] * 127 + 128);
            }
        }
    }

    image.writeToJPEG("test.jpg", 90);

    FastNoiseSIMD::FreeNoiseSet(noiseSet);

    return 0;
}
