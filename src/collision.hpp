//
//  collision.hpp
//  GigaRay
//
//  Created by Yohan Poirier-Ginter on 2018-04-24.
//
//

#ifndef collision_hpp
#define collision_hpp

#include <stdio.h>
#include "ray.hpp"
#include "shape.hpp"
#include "vector.hpp"

class Collision {
public:
    const Ray& ray;
    Shape& shape;
    Vector position;
    Vector normal;
    float distance;
    Collision(const Ray& ray, Shape& shape, Vector position, Vector normal, float distance);
    Collision& operator=(const Collision& other);
};

#endif /* collision_hpp */
