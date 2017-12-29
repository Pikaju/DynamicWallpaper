#pragma once

class Water
{
public:
    inline Water(float height) : m_height(height) {  }
    inline ~Water() {  }

    inline float getHeight() const { return m_height; }
private:
    float m_height;
};
