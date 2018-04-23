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
#include "scene.hpp"
#include "vector.hpp"

class Camera : public ofCamera {
public:
    void render(Film& film, const Scene& scene);
    void toggleOrtho();
    double move_speed = 0.1;
    void reset();
};

#endif /* camera_hpp */
