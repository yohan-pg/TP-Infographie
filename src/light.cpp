//
//  light.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "light.hpp"
#include "scene.hpp"


Light::Light() {
    primitive.setRadius(0.1);
}

Color Light::cast(const Vector& target, bool trace) const {
    return Color(0,0,0,0);
}

void Light::draw() {
    primitive.setPosition(getPosition());
    primitive.draw();
}

Color PointLight::cast(const Vector& target, bool trace) const {
    Vector pos = getPosition();
    auto ray = Ray(pos, target);
    auto hit = scene.intersect(ray);
    if (hit && ((hit->position - pos).length() < ((target - pos).length() - 0.001))) {
        return Color::black;
    } else {
        return color * intensity;
    }
}

Color SpotLight::cast(const Vector& target) const {
    Vector pos = getPosition();
    Vector dir = getOrientationEuler();
    auto ray = Ray(pos, target - pos);
    auto hit = scene.intersect(ray);
    if (hit) {
        return Color::black;
    } else {
        float x = max((target - pos).dot(dir), 0.0f);
        return color * intensity * x * size;
    }
}

Color AmbientLight::cast(const Vector& target) const {
    return color * intensity;
}

string Light::getName() const{
    return "Light";
}

string PointLight::getName() const{
    return "PointLight";
}

string SpotLight::getName() const{
    return "SpotLight";
}

string AmbientLight::getName() const{
    return "AmbientLight";
}

