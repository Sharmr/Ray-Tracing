#ifndef THING_LIST_HPP
#define THING_LIST_HPP

#include "thing.hpp"

#include <memory>
#include <vector>

using std::shared_ptr; //autmoatically deleted when it no longer references anything
using std::make_shared;
//make_shared is to allocate a new instance of a thing
//shared_ptr<double> double_ptr = make_shared<double>(0.37);
//shared_ptr<vec3> vec_ptr = make_shared<vec3>(0.123,3.21, 1.897); 
//and so on
//you can also do:
//auto double_ptr = make_shared<double>(0.37);
//auto vec_ptr = make_shared<vec3>(0.123,3.21, 1.897);
//auto sphere_ptr = make_shared<sphere>(point3(0,0,0), 1.0);


class thing_list : public thing {
public:
    thing_list() {}
    thing_list(shared_ptr<thing> object) {add(object);}
    
    void clear() {objects.clear();}
    void add(shared_ptr<thing> object) {objects.push_back(object);}

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

private:
    std::vector<shared_ptr<thing>> objects;
};

//iterates through the list checking if a ray hits anything. If something is hit,

bool thing_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for(const auto& object : objects) {
        if(object -> hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

#endif