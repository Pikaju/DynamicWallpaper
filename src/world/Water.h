#pragma once

#include "../math/Ray.h"

class Water
{
public:
    /** Creates a water object.
     *  @param height The height of the water without waves.
     */
    Water(float height);
    ~Water();

    /** Reflects a ray of light.
     *  @param position The location, where the light hit the water's surface
     *  @param direction The direction of the light that hit the water
     *  @return A new ray, starting from the waters surface, pointing in the reflected direction.
     */
    Rayf reflectRay(const Vec3f& position, const Vec3f& direction) const;

    /** Calculates the color that a ray of light should have after being reflected off of the water surface.
     *  @param color The color of the incoming ray of light.
     *  @return The color of the reflected ray of light.
     */
    Vec3f reflectColor(const Vec3f& color) const;

    /** @return True, if the point is underneath the water's surface. */
    inline bool isInWater(const Vec3f& point) const { return point.y < getHeight(); }

    /** @return The height of the water's surface. */
    inline float getHeight() const { return m_height; }
private:
    float m_height;
};
