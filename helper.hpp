#ifndef HELPER_HPP
#define HELPER_HPP

#include <limits>
#include "vec3.hpp"
#include "thing.hpp"
#include <cstdlib>
#include "material.hpp"

const double infinity = std::numeric_limits<double>::infinity();

double random_double() {
    //random number in [0,1)
    return rand()/(RAND_MAX + 1.0);
}

double random_double(double min, double max) {
    //random number in [min, max)
    return min + (max - min) * random_double();
}

vec3 random_v() {
        return vec3(random_double(), random_double(), random_double());
}
vec3 random_v(double min, double max) {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}
// we want to find a random point in a unit sphere tangent to a point on the main sphere
//for use in a lambertian surface
vec3 random_in_unit_sphere() {
    while(true) {
        auto p = random_v(-1, 1);
        if(p.length_squared() >= 1) continue;
        return p;
    }
}
vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

double clamp(double x, double min, double max) {
    if(x < min) return min;
    if(x > max) return max;
    return x;
}

//takes input direction of ray v incident on surface with normal n.
//output is the direction of the reflected ray
//draw a little diagram if you want to see how it works
vec3 reflect(const vec3& v, const vec3& n) {
    return v - n * dot(v, n) * 2;
}

//refraction using snell's law
//v is the incident ray
//n is the surface normal
// refracted is a reference to the refracted ray- we give it the value we need to.
// let t be the trnsmitted ray
// everything is a unit vector
// index of refraction = (n cross t)/(n cross v)
// we express v and t as v = v_parallel + v_perpend and similarly for t
// v = (n.v) n + (n cross v) cross n
// t = (n.t) n + (n cross t) cross n
// so we have index*(n cross v) = n cross t
// we plug the above into the equation for t
// t = (n.t) n + index * (n cross v) cross n
// but from the equation for v we have:
// t = (n.t) n + index * (v - (n.v)n)
// (n.t)n is perpendicular to v-(n.v)n [draw a bloody diagram]
// therefore we can do this:
// |t|^2 = (n.t)^2 + index^2 |v - (n.v)n|^2 
// remember that time when we said everything's a unit vector?
// Call it Checkhov's unit vector
// 1 = (n.t)^2 + index^2 (1 - (n.v)^2)
// (n.t) = sqrt (1 - index^2(1 - (n.v)^2)) 
// you plug that back into the equation for t (yeah, remember him from episode 7? you though we were done with him?)
// t = sqrt (1 - index^2(1 - (n.v)^2)) n + index * (v - (n.v)n)
bool refract(const vec3& v_i, const vec3& n_i, float index_of_refraction, vec3& refracted) {
    vec3 uv = unit_vector(v_i); //unit vector form of the incident ray
                            //so that we don't have to divide by maginitude
    auto v = unit_vector(v_i);
    auto n = unit_vector(n_i);
    float dt  = dot(uv, n);
    float disc = 1.0 - index_of_refraction * index_of_refraction * (1.0 - (dt * dt));
    if (disc > 0) {
        refracted = (v - n * dot(n, v)) * index_of_refraction - n * sqrt(disc);
        return true; 
    }
    else {
        return false;
    }
}


color ray_color(const ray& r, const thing& world, int depth) {
    hit_record rec;

    if (depth <= 0)
        return color(0, 0, 0);

    if(world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return color(0, 0, 0); 
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0); 
}

#endif