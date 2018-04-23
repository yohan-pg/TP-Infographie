//
//  ray.hpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#ifndef ray_hpp
#define ray_hpp

#include <stdio.h>
#include "ofMain.h"


class Ray {
public:
    ofVec3f position;
    ofVec3f direction;
    
    Ray();
    Ray(ofVec3f direction);
    Ray(ofVec3f position, ofVec3f direction);
};

#endif /* ray_hpp */

