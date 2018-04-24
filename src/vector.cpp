//
//  vector.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "vector.hpp"

Normal::Normal() : Vector(0,0,0) {};

Normal::Normal(float x, float y, float z) : Vector(x, y, z) {
    normalize();
};

Normal::Normal(Vector v) : Vector(v.x, v.y, v.z) {
    normalize();
};
