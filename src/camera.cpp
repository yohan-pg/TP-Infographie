//
//  camera.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "camera.hpp"

void Camera::toggleOrtho() {
    if (getOrtho()) {
        disableOrtho();
    } else {
        enableOrtho();
    }
}


void Camera::render(Film& film, const Scene& scene) {
    
//    Vector imageplane_up = Vector(0, 1, 0).cross(camera.getGlobalOrientation());
//    Vector
    
    for (int i = 0; i < film.getWidth(); i++) {
        for (int j = 0; j < film.getHeight(); j++) {
//            Ray ray = primary_ray(i, j, width, height, scene);
//            film.setColor(i, j, scene.trace(ray));
        }
    }
}


void Camera::reset() {
    setPosition(Vector(0.f, 0.f, 100.f));
    setOrientation(Vector(0.f, 0.f, 0.f));
    setScale(1.f);
}
