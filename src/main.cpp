#include <iostream>

#include "math/Vec3.h"
#include "math/Ray.h"

#include <FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD.h>
#include <stb/stb_image_write.h>

int main(int argc, char** argv)
{
    FastNoiseSIMD* myNoise = FastNoiseSIMD::NewFastNoiseSIMD();

    // Get a set of 16 x 16 x 16 Simplex Fractal noise
    float* noiseSet = myNoise->GetSimplexFractalSet(0, 0, 0, 256, 256, 1, 1.5f);
    int index = 0;

    unsigned char image[256 * 256 * 3];

    for (int x = 0; x < 256; x++)
    {
        for (int y = 0; y < 256; y++)
        {
            for (int z = 0; z < 1; z++)
            {
                std::cout << noiseSet[index++] << std::endl;
                image[(x + y * 256) * 3 + 0] = noiseSet[index] * 127 + 128;
                image[(x + y * 256) * 3 + 1] = noiseSet[index] * 127 + 128;
                image[(x + y * 256) * 3 + 2] = noiseSet[index] * 127 + 128;
            }
        }
    }

    stbi_write_jpg("test.jpg", 256, 256, 3, reinterpret_cast<float*>(image), 90);

    FastNoiseSIMD::FreeNoiseSet(noiseSet);

    return 0;
}
