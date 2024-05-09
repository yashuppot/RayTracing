/***************************************************************
* Description: Header file for the Sphere class, a subclass    *
*              of hittable representing a sphere object in     *
*              the scene.                                      *                           
***************************************************************/

#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h" // Include necessary header files.
#include "vec3.h"

// Class representing a sphere object.
class sphere : public hittable {
public:
    // Constructors:
    sphere(const point3& center, double radius) : center(center), radius(fmax(0, radius)) {}

    // Method to check for ray-sphere intersection.
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        vec3 oc = center - r.origin(); // Vector from ray origin to sphere center.
        auto a = r.direction().length_squared(); // Squared length of ray direction.
        auto h = dot(r.direction(), oc); // Projection of oc onto ray direction.
        auto c = oc.length_squared() - radius * radius; // Squared distance from ray origin to sphere center minus squared radius.

        auto discriminant = h * h - a * c; // Discriminant of quadratic equation.
        if (discriminant < 0) {
            return false; // No intersection if discriminant is negative.
        }

        auto sqrtd = sqrt(discriminant); // Square root of discriminant.

        auto root = (h - sqrtd) / a; // First root of quadratic equation.

        // Check if the first root is within the specified ray interval.
        if (!ray_t.surrounds(root)) {
            root = (h + sqrtd) / a; // Second root of quadratic equation.
            // Check if the second root is within the specified ray interval.
            if (!ray_t.surrounds(root)) {
                return false; // No intersection if both roots are outside the interval.
            }
        }

        // Record intersection details.
        rec.t = root; // Update intersection parameter t.
        rec.p = r.at(rec.t); // Compute intersection point.
        vec3 outward_normal = (rec.p - center) / radius; // Compute outward normal vector.
        rec.set_face_normal(r, outward_normal); // Set face normal of hit record.

        return true; // Intersection found.
    }

private:
    point3 center; // Center of the sphere.
    double radius; // Radius of the sphere.
};

#endif // SPHERE_H