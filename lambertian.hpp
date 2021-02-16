#ifndef LAMBERTIAN_HPP
#define LAMBERTIAN_HPP

#include "material.hpp"
#include "helper.hpp"

class lambertian : public material {
public:
    lambertian(const color& a) : albedo(a) {} 
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const override;
private:
    color albedo;
};

bool lambertian::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
    auto scatter_direction = rec.normal + random_unit_vector();
    if(scatter_direction.near_zero())
        scatter_direction = rec.normal;

    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}

#endif