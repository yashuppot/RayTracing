/***************************************************************
* Description: Header file for general utilities and constants *
*              used in ray tracing.                            *
***************************************************************/

#ifndef RT_GENERAL_H
#define RT_GENERAL_H

#include <cmath> // Include necessary standard libraries.
#include <iostream>
#include <limits>
#include <memory>

// Std Usings
using std::make_shared; 
using std::shared_ptr;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity(); // Define infinity constant.
const double pi = 3.1415926535897932385; // Define pi constant.

// Utility functions

// Convert degrees to radians.
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180; // Formula to convert degrees to radians.
}

// Generate a random double in the range [0, 1).
inline double random_double() {
    return rand() / (RAND_MAX + 1.0); // Generate a random double using rand() function.
}

// Generate a random double in the specified range [min, max).
inline double random_double(double min, double max) {
    return min + (max - min) * random_double(); // Generate a random double within the specified range.
}

// Headers
#include "color.h" // Include necessary custom headers.
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif // RT_GENERAL_H