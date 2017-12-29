#include "Fog.h"

#include "sky/Sky.h"

#define LERP(a, b, x) (a + (b - a) * x)
#define CLAMP(x, min, max) (x < min ? min : (x > max ? max : x))

Fog::Fog()
{
}

Fog::~Fog()
{
}

Vec3f Fog::applyFog(const Vec3f& color, const Sky& sky, const Vec3f& p0, const Vec3f& p1) const
{
    float distance = (p1 - p0).length();

    // Ground fog
    const float groundFogHeight = -8.0f;

    float high = std::max(p0.y, p1.y);
    float low = std::min(p0.y, p1.y);
    float percentageInFog = CLAMP((groundFogHeight - low) / (high - low), 0.0f, 1.0f);
    float distanceInGroundFog = distance * percentageInFog;
    float depthMultiplier = std::max(groundFogHeight - low, 0.0f) / 8.0f;

    return LERP(color, sky.getColor(), log((distance + distanceInGroundFog * depthMultiplier) / 512.0f + 1.0f));
}
