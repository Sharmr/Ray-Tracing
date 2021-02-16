#ifndef CAMERA_HPP
#define CAMERA_HPP

extern const double ASPECT_RATIO;

class camera {
public:
    camera() :  viewport_height(2.0), viewport_width(ASPECT_RATIO * viewport_height), 
                focal_length(1.0), origin(point3(0,0,0)), horizontal(vec3(viewport_width,0,0)),
                vertical(vec3(0,viewport_height,0)) {
                    lower_left_corner = origin - horizontal/2 
                                        - vertical/2 - vec3(0, 0, focal_length);
                }
    camera(const double &vh, const double &f) : viewport_height(vh), 
                viewport_width(ASPECT_RATIO * viewport_height), 
                focal_length(f), origin(point3(0,0,0)), horizontal(vec3(viewport_width,0,0)),
                vertical(vec3(0,viewport_height,0)) {
                    lower_left_corner = origin - horizontal/2 
                                        - vertical/2 - vec3(0, 0, focal_length);
                }
    ray get_ray(double u, double v) {
        return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
    }
private:

    double viewport_height;
    double viewport_width;
    double focal_length;
    point3 origin;
    vec3 horizontal;
    vec3 vertical;
    vec3 lower_left_corner;
};

#endif