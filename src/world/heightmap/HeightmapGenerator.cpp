#include "HeightmapGenerator.h"

#include <FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD.h>

void HeightmapGenerator::generate(Heightmap& heightmap, unsigned int seed)
{
    FastNoiseSIMD* noise = FastNoiseSIMD::NewFastNoiseSIMD();
    noise->SetSeed(seed);
    //noise->SetSeed(0);
    noise->SetFractalOctaves(6);
    noise->SetFrequency(0.003f);

    for (unsigned int x = 0; x < heightmap.m_width; x++) {
        for (unsigned int z = 0; z < heightmap.m_length; z++) {
            generateChunk(heightmap.getChunkAt(x, z), x, z, noise);
        }
    }

    delete noise;
}

void HeightmapGenerator::generateChunk(Chunk<CHUNK_SIZE>* chunk, int cx, int cz, FastNoiseSIMD* noise)
{
    float* heightSet = noise->GetSimplexFractalSet(cx * CHUNK_SIZE, 0, cz * CHUNK_SIZE, CHUNK_SIZE, 1, CHUNK_SIZE, 1.5f);

    for (unsigned int x = 0; x < CHUNK_SIZE; x++) {
        for (unsigned int z = 0; z < CHUNK_SIZE; z++) {
            float height = heightSet[x * CHUNK_SIZE + z];

            chunk->setHeightAt(x, z, height * 64.0f);
        }
    }

    FastNoiseSIMD::FreeNoiseSet(heightSet);

    /*float* n0 = noise->GetCellularSet(cx * CHUNK_SIZE, 0, cz * CHUNK_SIZE, CHUNK_SIZE, 1, CHUNK_SIZE, 1.0f);
    float* n1 = noise->GetCellularSet(cx * CHUNK_SIZE, 0, cz * CHUNK_SIZE, CHUNK_SIZE, 1, CHUNK_SIZE, 2.0f);
    float* n2 = noise->GetCellularSet(cx * CHUNK_SIZE, 0, cz * CHUNK_SIZE, CHUNK_SIZE, 1, CHUNK_SIZE, 4.0f);
    float* n3 = noise->GetCellularSet(cx * CHUNK_SIZE, 0, cz * CHUNK_SIZE, CHUNK_SIZE, 1, CHUNK_SIZE, 8.0f);
    float* n4 = noise->GetCellularSet(cx * CHUNK_SIZE, 0, cz * CHUNK_SIZE, CHUNK_SIZE, 1, CHUNK_SIZE, 16.0f);
    float* n5 = noise->GetCellularSet(cx * CHUNK_SIZE, 0, cz * CHUNK_SIZE, CHUNK_SIZE, 1, CHUNK_SIZE, 32.0f);

    for (unsigned int x = 0; x < CHUNK_SIZE; x++) {
        for (unsigned int z = 0; z < CHUNK_SIZE; z++) {
            float noise = n0[x * CHUNK_SIZE + z] / 1.0f
                + n1[x * CHUNK_SIZE + z] / 2.0f
                + n2[x * CHUNK_SIZE + z] / 4.0f
                + n3[x * CHUNK_SIZE + z] / 8.0f
                + n4[x * CHUNK_SIZE + z] / 16.0f
                + n5[x * CHUNK_SIZE + z] / 32.0f
                ;
            chunk->setHeightAt(x, z, (noise * 2.0f - 1.0f) * 64.0f);
        }
    }

    FastNoiseSIMD::FreeNoiseSet(n0);
    FastNoiseSIMD::FreeNoiseSet(n1);
    FastNoiseSIMD::FreeNoiseSet(n2);
    FastNoiseSIMD::FreeNoiseSet(n3);
    FastNoiseSIMD::FreeNoiseSet(n4);
    FastNoiseSIMD::FreeNoiseSet(n5);*/
}
