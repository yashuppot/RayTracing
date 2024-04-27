#ifndef RT_GENERAL_H
#define RT_GENERAL_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>


// Std Usings
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

//Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180;
}

inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}

// Headers

#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif