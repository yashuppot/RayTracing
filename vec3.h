/***************************************************************
* Description: Header file for 3D vector class and related     *
*              vector operations.                              *
***************************************************************/

#ifndef VEC3_H
#define VEC3_H

#include "rt_general.h" // Include necessary header files.

// Define a class for 3D vectors.
class vec3 {
public:
    double e[3]; // Array to store the vector components.

    // Constructors:
    vec3() : e{0,0,0} {}
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    // Accessor functions for vector components.
    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    // Overloaded operators:
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); } // Negation operator (vector negate).
    double operator[](int i) const { return e[i]; } // Array access operator (access vector coordinates).
    double& operator[](int i) { return e[i]; } // Array operator returning a reference to vector coordinates.

    // Compound assignment operators:
    vec3& operator+=(const vec3 v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this; // Return a reference to the modified vector.
    }

    vec3& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator/=(double t) {
        return *this *= (1 / t);
    }

    // Vector length calculation:
    double length() const {
        return sqrt(length_squared());
    }

    // Squared vector length calculation (faster than length()).
    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    // Static methods for generating random vectors:
    static vec3 random();
    static vec3 random(double min, double max);
};

// Alias for 3D points.
using point3 = vec3;

// Utility functions for vector operations:

// Output stream operator for vectors.
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// Addition of two vectors.
inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

// Subtraction of two vectors.
inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// Scalar multiplication of a vector.
inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

// Scalar division of a vector.
inline vec3 operator/(const vec3& v, double t) {
    return vec3(v.e[0]/t, v.e[1]/t, v.e[2]/t);
}

// Dot product of two vectors.
inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

// Cross product of two vectors.
inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// Normalization of a vector.
inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

// Generate a random point in a unit sphere.
inline vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1,1);
        if (p.length_squared() < 1) {
            return p;
        }
    }
}

// Generate a random unit vector.
inline vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

// Generate a random point on a hemisphere given a normal vector.
inline vec3 random_on_hemisphere(const vec3& normal) {
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) {
        return on_unit_sphere;
    }
    else {
        return -on_unit_sphere;
    }
}

#endif