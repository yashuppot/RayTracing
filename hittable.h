/***************************************************************
* Description: Header file for the Hittable class and related   *
*              hit_record struct used in ray tracing.          *
***************************************************************/

#ifndef HITTABLE_H
#define HITTABLE_H

#include "rt_general.h" // Include necessary header files.

// Class representing information about a hit between a ray and an object.
class hit_record {
public:
    point3 p; // Point of intersection.
    vec3 normal; // Surface normal at the point of intersection.
    double t; // Parameter value of the hit along the ray.
    bool front_face; // Indicates whether the ray hits the front or back side of the object.

    // Set the face normal based on the ray direction and outward normal.
    void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0; // Check if the ray is hitting the front face.
        normal = front_face ? outward_normal : -outward_normal; // Set the normal direction accordingly.
    }
};

// Abstract base class for hittable objects.
class hittable {
public:
    virtual ~hittable() = default; // Virtual destructor.

    // Method to check for ray-object intersection.
    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif // HITTABLE_H