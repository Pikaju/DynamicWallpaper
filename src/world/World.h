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

    TraceResult trace(const Rayf& ray, const TraceParamter& parameter) const override;

    bool inShadow(const Vec3f& position) const;
    inline float getShadowMultiplier(const Vec3f& position) const { return inShadow(position) ? 0.5f : 1.0f; }

private:
    Heightmap m_heightmap;
    Sky m_sky;
    Fog m_fog;
    Water m_water;
};
