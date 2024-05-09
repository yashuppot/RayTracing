/***************************************************************
* Description: Header file for the Color functions and types,   *
*              providing utilities for working with colors in   *
*              ray tracing.                                     *
***************************************************************/

#ifndef COLOR_H
#define COLOR_H

#include "vec3.h" // Include necessary header files.
#include "interval.h"
#include "rt_general.h"

using color = vec3; // Alias for vec3 representing color.

// Function to write color information to output stream.
void write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color.x(); // Red component of the pixel color.
    auto g = pixel_color.y(); // Green component of the pixel color.
    auto b = pixel_color.z(); // Blue component of the pixel color.

    // Clamp color intensities to the range [0.0, 0.999] and convert to byte values.
    static const interval intensity(0.0, 0.999);
    int rbyte = int(255.999 * intensity.clamp(r)); // Convert and clamp red intensity.
    int gbyte = int(255.999 * intensity.clamp(g)); // Convert and clamp green intensity.
    int bbyte = int(255.999 * intensity.clamp(b)); // Convert and clamp blue intensity.

    // Write the color values to the output stream.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif // COLOR_H