/***************************************************************
* Description: Header file for the HittableList class, a       *
*              subclass of hittable representing a list of     *
*              hittable objects in the scene.                  *
***************************************************************/

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h" // Include necessary header files.
#include "rt_general.h"

#include <vector> // Include necessary standard library headers.

// Class representing a list of hittable objects.
class hittable_list : public hittable {
public:
    std::vector<shared_ptr<hittable>> objects; // Vector to store pointers to hittable objects.

    // Constructors:
    hittable_list() {} // Default constructor.
    hittable_list(shared_ptr<hittable> object) { add(object); } // Constructor with initial object.

    // Clear the list of objects.
    void clear() { objects.clear(); }

    // Add a new object to the list.
    void add(shared_ptr<hittable> object) {
        objects.push_back(object);
    }

    // Method to check for ray-object intersection with all objects in the list.
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        hit_record temp_rec; // Temporary hit record.
        bool hit_anything = false; // Flag indicating if any object is hit.
        auto closest_so_far = ray_t.max; // Initialize closest intersection parameter to the maximum value.

        // Iterate over all objects in the list.
        for (const auto& object : objects) {
            // Check for intersection with the current object.
            if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
                hit_anything = true; // Update hit flag.
                closest_so_far = temp_rec.t; // Update closest intersection parameter.
                rec = temp_rec; // Update hit record with the new intersection details.
            }
        }

        return hit_anything; // Return whether any object is hit.
    }
};

#endif // HITTABLE_LIST_H