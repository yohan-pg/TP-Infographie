//
//  ray.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "ray.hpp"

Ray::Ray() {};

Ray::Ray(ofVec3f position, ofVec3f direction) : position(position), direction(direction) {}

Ray::Ray(ofVec3f direction): direction(direction) { }
