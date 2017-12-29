#pragma once

#include "../../math/Vec3.h"

class Sky
{
public:
    Sky();
    ~Sky();

    Vec3f getColor() const;
};
