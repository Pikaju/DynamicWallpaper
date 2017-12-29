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
    Vec3f direction = p1 - p0;
    float distance = direction.length();
    direction.y = 0.0f;
    float horizontalDistance = direction.length();

    float high = std::max(p0.y, p1.y);
    float low = std::min(p0.y, p1.y);

    float fog = fogAntiderivative(high) - fogAntiderivative(low);
    fog *= horizontalDistance / (high - low);

    return LERP(color, sky.getColor(), CLAMP(fog, 0.0f, 1.0f));
}

float Fog::fogAntiderivative(float height) const
{
    // f(x)=e^(-1/32*x)*0.002
    // F(x)=(e^(-1/32*x))/(-1/32)*0.002
    return exp(-1.0f / 32.0f * height) / (-1.0f / 32.0f) * 0.002f;
}
