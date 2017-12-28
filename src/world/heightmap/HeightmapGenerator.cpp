#include "HeightmapGenerator.h"

#include <FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD.h>

void HeightmapGenerator::generate(Heightmap& heightmap)
{
    FastNoiseSIMD* noise = FastNoiseSIMD::NewFastNoiseSIMD();

    for (unsigned int x = 0; x < heightmap.m_width; x++) {
        for (unsigned int z = 0; z < heightmap.m_length; z++) {
            generateChunk(heightmap.getChunkAt(x, z), x, z, noise);
        }
    }

    delete noise;
}

void HeightmapGenerator::generateChunk(Chunk<CHUNK_SIZE>* chunk, int cx, int cz, FastNoiseSIMD* noise)
{
    float* noiseSet = noise->GetSimplexFractalSet(cx * CHUNK_SIZE, 0, cz * CHUNK_SIZE, CHUNK_SIZE, 1, CHUNK_SIZE, 1.5f);

    for (unsigned int x = 0; x < CHUNK_SIZE; x++) {
        for (unsigned int z = 0; z < CHUNK_SIZE; z++) {
            chunk->setHeightAt(x, z, noiseSet[x * CHUNK_SIZE + z] * 64.0f);
        }
    }

    FastNoiseSIMD::FreeNoiseSet(noiseSet);
}
