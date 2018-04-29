//
//  ray.hpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#pragma once

#ifndef ray_hpp
#define ray_hpp

#include <stdio.h>
#include "ofMain.h"
#include "vector.hpp"
#include "transform.hpp"


class Ray {
public:
    Vector position;
    Normal direction;
    
    bool marked = false;
    
    Ray();
    Ray(Vector position, Vector target);
    Ray(Vector position, Normal direction);
    
    Ray operator*(Transform xform) const;
    
    Vector at(float t) const;
    
    Ray(const Ray &ray) {position = ray.position; direction = ray.direction; marked=ray.marked; };
    
    friend std::ostream& operator<< (std::ostream& stream, const Ray& ray);
};

extern Ray unit_ray;


#endif /* ray_hpp */

