# Ray Tracing Project

This project implements a simple ray tracing renderer in C++ using algorithms from [Ray Tracing In One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html). It includes the following components:

- **vec3**: A vector class for 3D geometry calculations.
- **interval**: A class representing intervals used in ray-object intersection calculations.
- **color**: Utilities for working with colors in ray tracing.
- **ray**: A class representing rays in the scene.
- **hittable**: Abstract base class for hittable objects in the scene.
- **hittable_list**: A list of hittable objects.
- **camera**: A camera class for rendering the scene using ray tracing.

## Usage

To use the ray tracer, include the necessary header files in your project and create a scene using the provided classes. Then, create a camera object and call the `render` method to generate an image of the scene.

```cpp
#include <iostream>
#include "rt_general.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"


int main() {

    hittable_list world;

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1),100));
    camera cam;
    
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.render(world);
}
