#pragma once

#include "Vec3.h"

template<typename T>
class Camera
{
public:
    Vec3<T> position;
    T yaw;
    T pitch;
    T fov;
    T aspectRatio;

    inline Camera(const Vec3<T>& position, T fov, T aspectRatio) : position(position), yaw(static_cast<T>(0)), pitch(static_cast<T>(0)), fov(fov), aspectRatio(aspectRatio) {  }
    inline Camera(const Vec3<T>& position, T yaw, T pitch, T fov, T aspectRatio) : position(position), yaw(yaw), pitch(pitch), fov(fov), aspectRatio(aspectRatio) {  }
    inline ~Camera() {  }

    inline Ray<T> getViewRay(T x, T y) const { return Ray<T>(position, yaw + x * aspectRatio * fov / static_cast<T>(2), pitch + y * fov / static_cast<T>(2)); }
    inline Vec3<T> getViewDirection(T x, T y) const { return getViewRay(x, y).direction; }
    inline Vec3<T> getViewDirection() const { return getViewDirection(static_cast<T>(0), static_cast<T>(0)); }
};
