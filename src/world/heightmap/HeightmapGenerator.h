#pragma once

#include "Heightmap.h"

class FastNoiseSIMD;

class HeightmapGenerator
{
public:
    static void generate(Heightmap& heightmap, unsigned int seed);
private:
    static void generateChunk(Chunk<CHUNK_SIZE>* chunk, int x, int z, FastNoiseSIMD* noise);
};
