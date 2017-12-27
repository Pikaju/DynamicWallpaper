#include <iostream>

#include "math/Vec3.h"
#include "math/Ray.h"

#include <FastNoiseSIMD/FastNoiseSIMD.h>

int main(int argc, char** argv)
{
    FastNoiseSIMD* myNoise = FastNoiseSIMD::NewFastNoiseSIMD();

    // Get a set of 16 x 16 x 16 Simplex Fractal noise
    float* noiseSet = myNoise->GetSimplexFractalSet(0, 0, 0, 16, 16, 16);
    int index = 0;

    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            for (int z = 0; z < 16; z++)
            {
                std::cout << noiseSet[index++] << std::endl;
            }
        }
    }

    FastNoiseSIMD::FreeNoiseSet(noiseSet);
    return 0;
}
