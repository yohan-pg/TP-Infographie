//
//  collision.cpp
//  GigaRay
//
//  Created by Yohan Poirier-Ginter on 2018-04-24.
//
//

#include "collision.hpp"

//Collision::Collision() :ray(unit_ray), shape(unit_shape) {}

Collision::Collision(const Ray& ray, Shape& shape, Vector position, Vector normal, float distance)
: ray(ray), shape(shape), position(position), normal(normal), distance(distance) {}

Collision& Collision::operator=(const Collision& other) {
//    this->ray = &other.ray;
//    this->position = other.position;
//    this->shape = &other.shape;
//    this->normal = other.normal;
//    this->distance = other.distance;
    return *this;
}


