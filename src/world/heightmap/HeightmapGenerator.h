#pragma once

#include "Heightmap.h"

class FastNoiseSIMD;

class HeightmapGenerator
{
public:
    static void generate(Heightmap& heightmap);
private:
    static void generateChunk(Chunk<CHUNK_SIZE>* chunk, int x, int z, FastNoiseSIMD* noise);
};
