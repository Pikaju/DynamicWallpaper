#include "Water.h"

Water::Water(float height) : m_height(height)
{
}

Water::~Water()
{
}

Rayf Water::reflectRay(const Vec3f& position, const Vec3f& direction) const
{
    // Reflect the direction vector along the surface normal
    Rayf ray(position, direction * Vec3f(1.0f, -1.0f, 1.0f));
    // Correct rays that have already reached heights below the surface
    ray.origin += ray.direction * (getHeight() - ray.origin.y);
    return ray;
}

Vec3f Water::reflectColor(const Vec3f& color) const
{
    return color * 0.5f + Vec3f(0.2f, 0.1f, 0.02f);
}
