//
//  collision.cpp
//  GigaRay
//
//  Created by Yohan Poirier-Ginter on 2018-04-24.
//
//

#include "collision.hpp"

Collision::Collision() {}

Collision::Collision(const Ray& ray, Shape& shape, Vector position, Vector normal)
: ray(&ray), shape(&shape), position(position), normal(normal), distance(distance) {}


Collision Missed = Collision();
