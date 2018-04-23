//
//  collision.hpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-16.
//
//

#ifndef collision_hpp
#define collision_hpp

#include <stdio.h>
#include "shape.hpp"
#include "ray.hpp"
#include "vector.hpp"

class Collision {
    bool hit = false;
    Ray ray;
    Shape shape;
    Vector position;
};


#endif /* collision_hpp */
