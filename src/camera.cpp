//
//  camera.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "camera.hpp"
#include "scene.hpp"

Camera::Camera() : Camera(60) {};

Camera::Camera(float fov) : ofCamera() {
    ofCamera::setFov(fov);
    image_size = tan(ofDegToRad(getFov())/2);
}

void Camera::toggleOrtho() {
    if (getOrtho()) {
        disableOrtho();
    } else {
        enableOrtho();
    }
}

void Camera::setFov(float fov) {}

void Camera::setOrtho(bool setting) {
    if (setting) {
        enableOrtho();
    } else {
        disableOrtho();
    }
}

Ray Camera::primaryRay(Film& film, float i, float j) {
    float screen_x = (i + 0.5) / film.width;
    float screen_y = (j + 0.5) / film.height;
    float cam_x = ofLerp(-1, 1, screen_x) * film.aspect * image_size;
    float cam_y = ofLerp(-1, 1, screen_y) * image_size;
    float focus_distance = (target - getPosition()).length();
    Vector endpoint = Vector(cam_x, cam_y, -1) * getGlobalTransformMatrix() ;
    return Ray(getPosition() + Sampler::uniform_circle() * aperture_size, endpoint);
}

void Camera::render(Film& film) {
    int x = Sampler::uniform_int(0, film.width);
    int y = Sampler::uniform_int(0, film.height);
    
    Color color = Color::black;
    float contrib = 1 / static_cast<float>(aa_samples);
    for (int i = 0; i < aa_samples; i++) {
        float dx = Sampler::uniform_float();
        float dy = Sampler::uniform_float();
        color += scene->trace(primaryRay(film, x+dx-0.5, y+dy-0.5));
    }

    film.set(x, y, color);
}

void Camera::reset() {
    setPosition(Vector(0.f, 0.f, 5.f));
    setOrientation(Vector(0.f, 0.f, 0.f));
    setScale(1.f);
}
