/***************************************************************
* Description: Header file for the Camera class, which handles  *
*              rendering of the scene using ray tracing.        *
***************************************************************/

#ifndef CAMERA_H
#define CAMERA_H

#include "rt_general.h" // Include necessary header files.
#include "hittable.h"

// Class representing a camera for ray tracing.
class camera {
public:
    double aspect_ratio = 1.0; // Aspect ratio of the camera.
    int image_width = 100; // Width of the rendered image.
    int samples_per_pixel; // Number of random samples per pixel.
    int max_depth = 10; // Maximum number of ray bounces.

    // Method to render the scene.
    void render(const hittable& world) {
        initialize(); // Initialize camera parameters.

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n"; // PPM image header.

        // Loop over each pixel row.
        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush; // Output progress.
            // Loop over each pixel column.
            for (int i = 0; i < image_width; i++) {
                color pixel_color(0, 0, 0); // Initialize pixel color.
                // Sample multiple rays per pixel and accumulate colors.
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(i, j); // Get ray for current pixel and sample.
                    pixel_color += ray_color(r, max_depth, world); // Accumulate color.
                }
                write_color(std::cout, pixel_samples_scale * pixel_color); // Write color to output stream.
            }
        }

        std::clog << "\rDone.                 \n"; // Output completion message.
    }

private:
    int image_height; // Height of the rendered image.
    point3 center; // Camera center.
    point3 pixel00_loc; // Location of top-left pixel.
    vec3 pixel_delta_u; // Change in pixel position along the x-axis
    vec3 pixel_delta_v; // Change in pixel position along the y-axis.
    double pixel_samples_scale; // Scale factor for pixel color samples.

    // Initialize camera parameters.
    void initialize() {
        image_height = int(image_width / aspect_ratio); // Compute image height based on aspect ratio.
        image_height = (image_height < 1) ? 1 : image_height; // Ensure minimum height of 1 pixel.

        pixel_samples_scale = 1.0 / samples_per_pixel; // Compute scale factor for pixel color samples.

        center = point3(0, 0, 0); // Set camera center.

        auto focal_length = 1.0; // Focal length of the camera.
        auto viewport_height = 2.0; // Height of the viewport.
        auto viewport_width = viewport_height * (double(image_width) / image_height); // Width of the viewport.

        auto viewport_u = vec3(viewport_width, 0, 0); // U-vector of the viewport.
        auto viewport_v = vec3(0, -viewport_height, 0); // V-vector of the viewport.

        pixel_delta_u = viewport_u / image_width; // Compute change in pixel position along the u-axis.
        pixel_delta_v = viewport_v / image_height; // Compute change in pixel position along the v-axis.

        auto viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2; // Upper-left corner of the viewport.
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v); // Location of top-left pixel.
    }

    // Get the ray corresponding to a pixel and sample.
    ray get_ray(int i, int j) const {
        auto offset = sample_square(); // Sample offset within the pixel.
        auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v); // Compute pixel location.
        auto ray_origin = center; // Camera origin.
        auto ray_direction = pixel_sample - ray_origin; // Ray direction.

        return ray(ray_origin, ray_direction); // Return the computed ray.
    }

    // Sample a point within the unit square.
    vec3 sample_square() const {
        return vec3(random_double() - 0.5, random_double() - 0.5, 0); // Return a random point within the unit square.
    }

    // Compute the color of a ray.
    color ray_color(const ray& r, int depth, const hittable& world) const {
        hit_record rec; // Hit record for ray-object intersection.
        if (depth <= 0) {
            return color(0, 0, 0); // Return black if maximum depth is reached.
        }
        if (world.hit(r, interval(0, infinity), rec)) { // Check for intersection with the scene.
            vec3 direction = random_on_hemisphere(rec.normal); // Random direction on the hemisphere.
            return 0.5 * ray_color(ray(rec.p, direction), depth - 1, world); // Return color from bounced ray.
        }
        // If no intersection, compute background color using a simple gradient.
        vec3 unit_direction = unit_vector(r.direction()); // Unit direction of the ray.
        auto a = 0.5 * (unit_direction.y() + 1.0); // Scale factor based on ray direction.
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0); // Linear interpolation for gradient.
    }
};

#endif // CAMERA_H