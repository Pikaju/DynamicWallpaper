#pragma once

class Vec3
{
public:
    float x;
    float y;
    float z;

    inline Vec3(float v = 0.0f) : x(v), y(v), z(v) {  }
    inline Vec3(float x, float y, float z) : x(x), y(y), z(z) {  }
    inline ~Vec3() {  }

};
