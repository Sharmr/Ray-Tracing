#include "header.hpp"

int main() {

    thing_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8));
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2));

    world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_ground));
    world.add(make_shared<sphere>(point3(0, -100.5, -1.0), 100, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0.0,-1.0), 0.5, material_left));
    world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

    std::ofstream pfile;
    pfile.open("output.ppm");
    pfile << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";

    camera cam;
    
    std::cerr << IMAGE_HEIGHT;
    for (int j = IMAGE_HEIGHT - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << '\n' << std::flush;
        for (int i = 0; i < IMAGE_WIDTH; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_p; ++s) {
                auto u = (i + random_double())/(IMAGE_WIDTH-1);
                auto v = (j + random_double())/(IMAGE_HEIGHT-1);

                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(pfile, pixel_color, samples_per_p);
        }
    }
    pfile.close();
}