#include "Fog.h"

#include "sky/Sky.h"

#define LERP(a, b, x) (a + (b - a) * x)

Fog::Fog()
{
}

Fog::~Fog()
{
}

Vec3f Fog::applyFog(const Vec3f& color, const Sky& sky, const Vec3f& p0, const Vec3f& p1) const
{
    float distance = (p1 - p0).length();
    return LERP(color, sky.getColor(), distance / (sqrt(512.0f * 512.0f * 2.0f)));
}
