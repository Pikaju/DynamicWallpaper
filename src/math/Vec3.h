#pragma once

template<typename T>
class Vec3
{
public:
    T x;
    T y;
    T z;

    inline Vec3(T v = static_cast<T>(0)) : x(v), y(v), z(v) {  }
    inline Vec3(T x, T y, T z) : x(x), y(y), z(z) {  }
    inline ~Vec3() {  }

    inline void set(T v) { set(v, v, v); }
    inline void set(T x, T y, T z) { this->x = x; this->y = y; this->z = z; }

    inline Vec3<T> operator+(const Vec3<T>& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    inline Vec3<T> operator-(const Vec3<T>& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    inline Vec3<T> operator*(const Vec3<T>& v) const { return Vec3(x * v.x, y * v.y, z * v.z); }
    inline Vec3<T> operator/(const Vec3<T>& v) const { return Vec3(x / v.x, y / v.y, z / v.z); }

    inline void operator+(const Vec3<T>& v) { set(x + v.x, y + v.y, z + v.z); }
    inline void operator-(const Vec3<T>& v) { set(x - v.x, y - v.y, z - v.z); }
    inline void operator*(const Vec3<T>& v) { set(x * v.x, y * v.y, z * v.z); }
    inline void operator/(const Vec3<T>& v) { set(x / v.x, y / v.y, z / v.z); }
};

typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;
