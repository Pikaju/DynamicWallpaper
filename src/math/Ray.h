#pragma once

template<typename T>
class Ray
{
public:
    Vec3<T> origin;
    Vec3<T> direction;

    inline Ray(const Vec3<T> origin, const Vec3<T> direction) : origin(origin), direction(direction) {  }

    Ray(const Vec3<T> origin, T yaw, T pitch) : origin(origin)
    {
        T rx = pitch;
		T ry = yaw;
		T cosrx = static_cast<T>(cos(rx));
		direction.x = static_cast<T>(sin(ry) * cosrx);
		direction.y = static_cast<T>(sin(rx));
		direction.z = static_cast<T>(cos(ry) * cosrx);
    }

    inline ~Ray() {  }

    inline Vec3<T> march(float distance) const { return origin + direction * distance; }
};
