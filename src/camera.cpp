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

Ray Camera::primaryRay(Film film, float i, float j) {
    float size = tan(ofDegToRad(getFov())/2);
    float screen_x = (i + 0.5) / film.width;
    float screen_y = (j + 0.5) / film.height;
    float cam_x = ofLerp(-1, 1, screen_x) * film.aspect * size;
    float cam_y = ofLerp(-1, 1, screen_y) * size;
    Vector target = Vector(cam_x, cam_y, -1) * getGlobalTransformMatrix();
    return Ray(getPosition(), target);
}

void Camera::render(Film& film) {
    for (int i = 0; i < film.width; i++) {
        for (int j = 0; j < film.width; j++) {
            film.set(i, j, scene.trace(primaryRay(film, i, j), 1));
        }
    }
}

void Camera::reset() {
    setPosition(Vector(0.f, 0.f, 50.f));
    setOrientation(Vector(0.f, 0.f, 0.f));
    setScale(1.f);
}
