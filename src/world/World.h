#pragma once

#include "heightmap/Heightmap.h"
#include "sky/Sky.h"
#include "Fog.h"
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
    Fog m_fog;
    Water m_water;
};
