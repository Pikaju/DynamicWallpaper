#include "Sky.h"

#define CLAMP(x, min, max) (x < min ? min : (x > max ? max : x))
#define LERP(a, b, x) (a + (b - a) * x)

Sky::Sky()
{
}

Sky::~Sky()
{
}

Vec3f Sky::getColor(const Vec3f& direction) const
{
    float sunAngle = getLightDirection().dot(direction * -1.0f);
    float sunAmount = CLAMP(pow(sunAngle, 256.0f), 0.0f, 1.0f);
    //Vec3f sunColor(1.0f, 1.0f, 1.0f);
    Vec3f sunColor(4.0f, 2.0f, 2.0f);

    return LERP(getColor() * (direction.y + 1.0f) / 1.0f, sunColor, sunAmount);
}

Vec3f Sky::getColor() const
{
    return Vec3f(0.2f, 0.6f, 0.5f);
    //return Vec3f(0.4f, 0.2f, 0.5f);
    //return Vec3f(0.5f, 0.6f, 0.9f);
    //return Vec3f(0.5f, 0.3f, 0.4f);
}

Vec3f Sky::getLightDirection() const
{
    return Vec3f(-0.5f, -0.015f, -0.75f).normalized();
}
