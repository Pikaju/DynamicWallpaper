#pragma once

#include "heightmap/Heightmap.h"
#include "sky/Sky.h"
#include "Fog.h"
#include "Water.h"

class World : public RayTracable
{
public:
    /** Creates a new World object.
     *  @param width The width of the heightmap in chunks.
     *  @param length The length of the heightmap in chunks.
     *  @param seed The seed used to generate the world, using the same seed will always create the same result.
     */
    World(unsigned int width, unsigned int length, unsigned int seed);
    ~World();

    /** See RayTracable for more information. */
    TraceResult trace(const Rayf& ray, const TraceParamter& parameter) const override;

    /**
     *  @return True, if a specific point in the scene is in shadow of the sky's light.
     */
    bool inShadow(const Vec3f& point) const;
private:
    Heightmap m_heightmap;
    Sky m_sky;
    Fog m_fog;
    Water m_water;
};
