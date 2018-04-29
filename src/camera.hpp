//
//  camera.hpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#pragma once

#ifndef camera_hpp
#define camera_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ray.hpp"
#include "film.hpp"
#include "vector.hpp"
#include "sampler.hpp"

class Camera : public ofCamera {
    float image_size;
public:
    int aa_samples = 1;
    float aperture_size = 0;
    Camera();
    Camera(float fov);
    Camera(Vector target);
    void render(Film& film);
    void toggleOrtho();
    void setFov(float fov);
    void setOrtho(bool setting);
    void setDof(float dof);
    double move_speed = 0.1;
    Ray primaryRay(Film& film, float x, float y, bool focused=false);
    void reset();
};

#endif /* camera_hpp */
