#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "vec3.hpp"
#include "thing.hpp"


class sphere : public thing {
public:
    sphere() {}
    sphere(point3 cen, double rad, shared_ptr<material> m): center(cen), radius(rad), mat_ptr(m){}
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
private:
    double radius;
    point3 center;
    shared_ptr<material> mat_ptr;
};

//equation of a sphere: (p-c).(p-c) = R*R where p is a point on the sphere and c is the center of the sphere
//subsituting the equation for a ray for p we have:
//(A + Bt - C).(A + Bt -C) = R*R
//t*t*(B.B) + 2*t*(A-C).B + (A-C).(A-C) - R*R = 0
//Solving for t gives us all t at which a particular ray intersects the sphere
//No roots means the ray does not hit the sphere
//1 root means the ray is tangential to the sphere
//2 roots means that the ray passes through the sphere

//The surface normal at any given point p on the sphere is : p-c
bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    double a = r.direction().length_squared();
    double b = 2 * (dot(oc, r.direction()));
    double c = oc.length_squared() - radius*radius;
    double discriminant = b*b - 4*a*c;

    if (discriminant < 0)
        return false;

    auto sd = sqrt(discriminant);

    auto root = ((-b) - sd)/(2 * a);

    if (root < t_min || root > t_max) {
        root = ((-b) + sd)/(2 * a);
        if (root < t_min || root > t_max)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center)/radius; //always normalized
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

#endif