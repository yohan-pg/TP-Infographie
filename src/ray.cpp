//
//  ray.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "ray.hpp"

Ray::Ray() {};

Ray::Ray(ofVec3f position, ofVec3f target)
    : position(position), direction((target - position).normalize()) {}


std::ostream& operator<< (std::ostream& os, const Ray& ray) {
    os << "[" << ray.position << "] -> [" << ray.direction << "]" << endl;
    return os;
}
