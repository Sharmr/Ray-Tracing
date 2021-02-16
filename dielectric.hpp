#ifndef DIELECTRIC_HPP
#define DIELECTRIC_HPP

#include "material.hpp"

class dielectric : public material {
public:
    dielectric(double i) : index(i) {}
private:
    double index;
};

#endif