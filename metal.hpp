#ifndef METAL_HPP
#define METAL_HPP

#include "material.hpp"

class metal : public material {
public:
    metal(color a) : albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
    const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()),rec.normal);
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
private:
    color albedo;
};

#endif