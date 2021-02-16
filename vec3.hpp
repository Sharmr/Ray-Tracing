#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>
#include <cmath>
#include "helper.hpp"

using std::sqrt;

//3d vector that can hold either RGB values or position values.
class vec3 {
public:
    vec3() : e{0,0,0,0} {}
    vec3(double a, double b, double c) : e{a, b, c, 0} {}
    vec3(double a, double b, double c, double d) : e{a, b, c, d} {
        if(d < 0.0)
            e[3] = 0.0;
        else if( d != 1.0)
            e[3] = 1.0;
    }

    double x() {return e[0];}
    double y() {return e[1];}
    double z() {return e[2];}

    vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}
    double operator[](int i) const {return e[i];} 

    vec3& operator+=(const vec3 &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];

        return *this;
    }

    vec3 operator*=(const double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;

        return *this;
    }

    vec3 operator/=(const double t) {
        return *this /= t;
    }

    double length_squared() {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2] ;
    }

    double length() {
        return sqrt(length_squared());
    }
    bool near_zero() const {
        const auto s = 1e-8;
        return (fabs(e[0] < s) && fabs(e[1] < s) && fabs(e[2] < s));
    }
public:
    double e[4];
};

using color = vec3;
using point3 = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return -v + u;
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3 &v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
    return  u.e[0] * v.e[0] +
            u.e[1] * v.e[1] +
            u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}


#endif