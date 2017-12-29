#include "Sky.h"

Sky::Sky()
{
}

Sky::~Sky()
{
}

Vec3f Sky::getColor(const Vec3f& direction) const
{
    return getColor() * (direction.y + 3.0f) / 3.0f;
}

Vec3f Sky::getColor() const
{
    //return Vec3f(0.2f, 0.6f, 0.5f);
    return Vec3f(0.4f, 0.2f, 0.5f);
    //return Vec3f(0.3f, 0.6f, 0.9f);
}
