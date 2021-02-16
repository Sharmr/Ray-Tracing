#ifndef RAY_HPP
#define RAY_HPP

#include "vec3.hpp"

//A ray has the equation r(t) = A + t.B, where r, A, and B are vectors: r is the ray itself,
//A is the starting point of the ray w.r.t origin, and B is the direction of the ray.

class ray {
public:
    ray() {}
    ray(const point3 &A, const vec3 &B) : orig(A), dir(B) {}

    point3 origin() const {return orig;}
    vec3 direction() const{return dir;}

    point3 at(double t) const {
        return orig + t*dir;
    }
private:
    point3 orig;
    vec3 dir;
};

#endif