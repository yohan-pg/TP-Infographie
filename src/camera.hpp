//
//  camera.hpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#ifndef camera_hpp
#define camera_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ray.hpp"
#include "film.hpp"
#include "vector.hpp"

class Camera : public ofCamera {
    float dof = 0;
public:
    void render(Film& film);
    void toggleOrtho();
    void setOrtho(bool setting);
    void setDof(float dof);
    double move_speed = 0.1;
    void reset();
    
};

#endif /* camera_hpp */
