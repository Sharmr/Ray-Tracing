#ifndef HEADER_HPP
#define HEADER_HPP

#include "helper.hpp"
#include "vec3.hpp"
#include "thing_list.hpp"
#include "color.hpp"
#include "ray.hpp"
#include "camera.hpp"
#include "sphere.hpp"
#include "lambertian.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>
#include <memory>
#include "metal.hpp"
#include "material.hpp"

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

//const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;
const int IMAGE_WIDTH = 400;
const double ASPECT_RATIO = 16.0/9.0;
const int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH/ASPECT_RATIO);
const int samples_per_p = 100;
const int max_depth = 50;

inline double degrees_to_radians(double d) {
    return d * pi / 180.0 ;
}


#endif