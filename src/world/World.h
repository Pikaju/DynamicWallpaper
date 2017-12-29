#pragma once

#include "heightmap/Heightmap.h"
#include "sky/Sky.h"
#include "Water.h"

class World : public RayTracable
{
public:
    World(unsigned int width, unsigned int length);
    ~World();

    TraceResult trace(const Rayf& ray) const override;

private:
    Heightmap m_heightmap;
    Sky m_sky;
    Water m_water;
};
