//
//  collision.hpp
//  GigaRay
//
//  Created by Yohan Poirier-Ginter on 2018-04-24.
//
//

#pragma once

#ifndef collision_hpp
#define collision_hpp

#include <stdio.h>
#include "ray.hpp"
#include "shape.hpp"
#include "vector.hpp"

class Collision {
public:
    const Ray* ray = NULL;
    Shape* shape = NULL;
    Vector position;
    Vector normal;
    float distance;
    Collision();
    Collision(const Ray& ray, Shape& shape, Vector position, Vector normal);
    explicit operator bool() const { return shape != NULL; };
};

extern Collision Missed;

#endif /* collision_hpp */
