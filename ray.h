#ifndef RAY_H
#define RAY_H

#include "vec3.h" // Include necessary header files.

// Class representing a ray in 3D space.
class ray { 
public:
    // Constructors:
    ray() {} // Default constructor.
    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {} // Parameterized constructor.

    // Accessor functions for ray properties:
    const point3& origin() const { return orig; } // Return immutable reference to the origin.
    const vec3& direction() const { return dir; } // Return immutable reference to the direction.
    
    // Compute the position of the ray at a given parameter value t.
    point3 at(double t) const {
        return orig + t * dir; // Compute position using ray equation.
    }

private:
    point3 orig; // Origin point of the ray.
    vec3 dir; // Direction vector of the ray.
};

#endif // RAY_H