//
//  collision.cpp
//  GigaRay
//
//  Created by Yohan Poirier-Ginter on 2018-04-24.
//
//

#include "collision.hpp"

Collision::Collision() :ray(unit_ray), shape(unit_shape) {}

Collision::Collision(const Ray& ray, const Shape& shape, Vector position, Vector normal, float distance)
: ray(ray), shape(shape), position(position), normal(normal), distance(distance) {}


