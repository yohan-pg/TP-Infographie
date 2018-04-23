//
//  camera.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "camera.hpp"
#include "scene.hpp"

void Camera::toggleOrtho() {
    if (getOrtho()) {
        disableOrtho();
    } else {
        enableOrtho();
    }
}

void Camera::setOrtho(bool setting) {
    if (setting) {
        enableOrtho();
    } else {
        disableOrtho();
    }
}

void Camera::setDof(float _dof) {
    dof = _dof;
}

void Camera::render(Film& film) {
    float scale = tan(180 * pi * getFov() * 0.5);
    for (int i = 0; i < film.width; i++) {
        for (int j = 0; j < film.width; j++) {
            float x = (2 * (i + 0.5) / (float)film.width - 1) * film.aspect * scale;
            float y = (1 - 2 * (j + 0.5) / (float)film.height) * scale;
//            Vec3f dir;
//            cameraToWorld.multDirMatrix(Vec3f(x, y, -1), dir);
//            dir.normalize();
            
            //            Ray ray = primary_ray(i, j, width, height, scene);
            //            film.setColor(i, j, scene.trace(ray));
            
            
        }
    }
}

void Camera::reset() {
    setPosition(Vector(0.f, 0.f, 50.f));
    setOrientation(Vector(0.f, 0.f, 0.f));
    setScale(1.f);
}
