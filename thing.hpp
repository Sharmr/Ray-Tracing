#ifndef THING_HPP
#define THING_HPP

#include "ray.hpp"
#include <cmath>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

class material;

struct hit_record {
    point3 p;
    vec3 normal;
    double t;
    shared_ptr<material> mat_ptr;
    bool front_face;

    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal: -outward_normal;
    }
};

class thing {
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif