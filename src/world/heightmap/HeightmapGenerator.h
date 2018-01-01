#pragma once

#include "Heightmap.h"

class FastNoiseSIMD;

class HeightmapGenerator
{
public:
    /** Generates a terrain heightmap using simplex noise.
     *  @param heightmap The heightmap that should be filled with terrain data.
     *  @param seed The seed to generate the heightmap, making it deterministic.
     */
    static void generate(Heightmap& heightmap, unsigned int seed);
private:
    static void generateChunk(Chunk<CHUNK_SIZE>* chunk, int x, int z, FastNoiseSIMD* noise);
};
