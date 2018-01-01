#pragma once

#include <math.h>

#include "Vec3.h"

#define RAD(x) (x / 180.0 * 3.14159265)

template<typename T>
class Ray
{
public:
    Vec3<T> origin;
    Vec3<T> direction;

    inline Ray(const Vec3<T> origin, const Vec3<T> direction) : origin(origin), direction(direction) {  }

    Ray(const Vec3<T> origin, T yaw, T pitch) : origin(origin)
    {
        double rx = RAD(pitch);
		double ry = RAD(yaw);
		double cosrx = cos(rx);
		direction.x = static_cast<T>(sin(ry) * cosrx);
		direction.y = static_cast<T>(sin(rx));
		direction.z = static_cast<T>(cos(ry) * cosrx);
    }

    inline ~Ray() {  }

    /** March along the ray for a certain distance.
     *  @param distance How far to follow the ray.
     *  @return The position the origin would be at when following the direction.
     */
    inline Vec3<T> march(float distance) const { return origin + direction * distance; }
};

typedef Ray<int> Rayi;
typedef Ray<float> Rayf;
typedef Ray<double> Rayd;
