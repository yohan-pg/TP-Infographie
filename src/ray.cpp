//
//  ray.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "ray.hpp"

Ray::Ray() {};

Ray::Ray(Vector position, Vector target) : position(position), direction(Normal(target - position)) {}

Ray::Ray(Vector position, Normal direction) : position(position), direction(direction) {}

Vector Ray::at(float t) const {
    return position + t * direction;
}

Ray Ray::operator*(Transform xform) const {
    return Ray(position * xform, direction);
}


std::ostream& operator<< (std::ostream& os, const Ray& ray) {
    os << "[" << ray.position << "] -> [" << ray.direction << "]";
    return os;
}

Ray unit_ray = Ray();
