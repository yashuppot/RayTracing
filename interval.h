#ifndef INTERVAL_H
#define INTERVAL_H

#include "rt_general.h" // Include necessary header files.

// Class representing a closed interval [min, max].
class interval {
public:
    double min, max; // Minimum and maximum values of the interval.

    // Constructors:
    interval() : min(+infinity), max(-infinity) {} // Default constructor initializes interval to an empty state.
    interval(double min, double max) : min(min), max(max) {} // Parameterized constructor.

    // Calculate the size of the interval.
    double size() const {
        return max - min; // Difference between max and min.
    }

    // Check if the interval contains a given value.
    bool contains(double x) const {
        return min <= x && x <= max; // Check if x is within the interval bounds.
    }

    // Check if the interval surrounds a given value.
    bool surrounds(double x) const {
        return min < x && x < max; // Check if x is strictly within the interval bounds.
    }

    // Clamp a value to the interval bounds.
    double clamp(double x) const {
        if (x < min) return min; // Clamp x to min if it's less than min.
        if (x > max) return max; // Clamp x to max if it's greater than max.
        return x; // Otherwise, return x itself.
    }

    // Static constants representing an empty and a universal interval.
    static const interval empty, universe;
};

// Define static constants representing an empty interval and a universal interval.
const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);

#endif // INTERVAL_H