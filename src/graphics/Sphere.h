#pragma once

#include "RayTracable.h"
#include "../math/Vec3.h"

class Sphere : public RayTracable
{
public:
    Vec3f position;
    float radius;

    inline Sphere(const Vec3f& position = Vec3f(), float radius = 1.0f) : position(position), radius(radius) {  }
    inline ~Sphere() override {  }

    TraceResult trace(const Rayf& ray) const override
    {
        TraceResult result;
        float range = 32.0f;
        float step = 0.125f;
        for (float distance = 0.0f; distance < range; distance += step) {
            if (intersects(ray.march(distance))) {
                result.intersects = true;
                result.distance = distance;
                return result;
            }
        }
        result.intersects = false;
        return result;
    }
private:
    inline bool intersects(const Vec3f& point) const { return (position - point).lengthSquared() < radius * radius; }
};
