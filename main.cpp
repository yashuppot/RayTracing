#include <iostream>
#include "vec3.h"
#include "color.h"
#include "ray.h"


double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = center - r.origin(); /* (vector from sphere center to ray origin)
                                    We do some fancy math using this
                                    Essentially we are checking if
                                    (center - r.origin() - t * r.direction()) dot (center - r.origin() - t * r.direction()) = r^2
                                    has solutions.
                                    If so there is an intersection.
                                    */
        auto a = dot(r.direction(), r.direction());
        auto h =  dot(r.direction(), oc); //(substitution for b to simplify algebra)
        auto c = dot(oc, oc) - radius * radius;
        auto discriminant = h * h - a * c;
        if (discriminant < 0 ) { 
            return -1.0;
        }
        else { 
            return (h - sqrt(discriminant)) / (a); // (smaller solution for)
        }
         //Solving the equation boiled down to solving a quadratic (you know the math)
}

color ray_color(const ray& r) {
    auto t =  (hit_sphere(point3(0,0,-1), 0.5, r));
    if (t > 0.0) {
        vec3 unit_normal = unit_vector(r.at(t) - vec3(0,0,-1)); // The normal is just the vector from the center to the point on the sphere
        return 0.5 * color(unit_normal.x() + 1, unit_normal.y() + 1, unit_normal.z() + 1);
    }
    vec3 unit_direction = unit_vector(r.direction()); //Scale so that length is 1
    auto a = 0.5*(unit_direction.y() + 1.0); // Transform range (-1 through 1 into 0 through 1)
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0); //Lerp blend the colours (blue through white, y=-1 means a=0 means full white)
}

int main() {

    // Image
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    //Camera
    auto focal_length = 1.0; //dist from camera to viewport

    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height); //Can't just use aspect ratio because of rounding (image width and height are int)
    auto camera_center = point3(0,0,0);

    //Viewport vectors (from top left corner)
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0); //top left to bottom left moves down across the y axis (right hand coords)

    // Delta vectors

    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v /image_height;
    
    // Upper left pixel on viewport
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2; //viewport_v is negative (subtracting it shifts up)
    auto pixel100_loc = viewport_upper_left + 0.5 * (pixel_delta_v + pixel_delta_u); // Inset the first pixel by half the delta values (pixels centered in rows and cols)

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) { //row
        std::clog << "\rScanLines remaining:" << (image_height - j) << ' ' << std::flush; //For slow renders (progress bar)
        for (int i = 0; i < image_width; i++) { //column (more red the further right we go)
            auto pixel_center = pixel100_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}