//
//  camera.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "camera.hpp"
#include "scene.hpp"

Camera::Camera() : Camera(45) {};

Camera::Camera(float fov) : ofCamera() {
    setFov(fov);
}

void Camera::toggleOrtho() {
    if (getOrtho()) {
        disableOrtho();
    } else {
        enableOrtho();
    }
}

void Camera::setFov(float fov) {
    ofCamera::setFov(fov);
    image_size = tan(ofDegToRad(getFov())/2);
}

void Camera::setOrtho(bool setting) {
    if (setting) {
        enableOrtho();
    } else {
        disableOrtho();
    }
}

Ray Camera::primaryRay(Film& film, float i, float j, bool focused) {
    float screen_x = i / film.width;
    float screen_y = j / film.height;
    float cam_x = ofLerp(-1, 1, screen_x) * film.aspect * 1.2 * image_size;
    float cam_y = ofLerp(1, -1, screen_y) * image_size;
    Vector focal_point = scene.selection == NULL ? Vector(0,0,0) : scene.selection->getPosition();
    float focal_distance = (focal_point - getPosition()).length();
    Vector endpoint = Vector(cam_x, cam_y, -1) * focal_distance * getGlobalTransformMatrix();
    Ray ray = Ray(getPosition() + Sampler::uniform_circle() * (focused ? 0 : aperture_size), endpoint);
    if (floor(i) == film.width/2 && floor(j) == film.height/2) {
        ray.marked = true;
    }
    return ray;
}

void Camera::render(Film& film) {
    vector<int> xs(film.width);
    iota(xs.begin(), xs.end(), 0);
    random_shuffle(xs.begin(), xs.end());
    
    vector<int> ys(film.height);
    iota(ys.begin(), ys.end(), 0);
    random_shuffle(ys.begin(), ys.end());
    
    for (int j = 0; j < xs.size(); j++) {
        int x = xs[j];
        int y = ys[j % ys.size()];
            Color color = Color::black;
            float contrib = 1 / static_cast<float>(aa_samples);
            for (int i = 0; i < aa_samples; i++) {
                float dx = aa_samples > 1 ? Sampler::uniform_float() : 0;
                float dy = aa_samples > 1 ? Sampler::uniform_float() : 0;
                color += scene.trace(primaryRay(film, x+dx, y+dy), scene.tracingDepth) * contrib;
            }
            film.set(x, y, color);
    }
}

void Camera::reset() {
    setNearClip(0.1);
    setPosition(Vector(0, 0.1, 5.f));
    setOrientation(Vector(0, 0.f, 0.f));
    setScale(1.f);
}
