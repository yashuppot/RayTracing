#ifndef VEC3_H
#define VEC3_H

#include "rt_general.h"

using std::sqrt;

class vec3 {
    public:
        double e[3];

        vec3() : e{0,0,0} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);} //overload negation operator (vector negate)
        double operator[](int i) const { return e[i];} //overload array access operator (access vector coordinates)
        double& operator[](int i) {return e[i];} //overload array operator but return a reference to vector coords (can modify)

        vec3& operator+=(const vec3 v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this; //this is a pointer to current vec3, dereferencing the pointer gets a reference (since we defined the return type to be a ref)
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

        double length() const {
            return sqrt(length_squared());
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }
};

using point3 = vec3;

// Vector Utility (inline resembles static methods from Java)

inline std::ostream& operator<<(std::ostream& out, const vec3& v) { //using a ref to vec3 (analgous to using a pointer in C to avoid copying)
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(double  t, const vec3& v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator/(const vec3& v, double  t) {
    return vec3(v.e[0]/t, v.e[1]/t, v.e[2]/t);
}

inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) { //our favourite super intuitive cross product formula =).
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

#endif