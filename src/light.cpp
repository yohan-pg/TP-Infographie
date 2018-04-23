//
//  light.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "light.hpp"
#include "scene.hpp"

Color PointLight::cast(const Vector& target) const {
    Vector pos = getPosition();
//    Collision coll = scene.trace(Ray(pos, target - pos));
//    if (coll.hit) {
//        return color * intensity;
//    }
    return scene.ambient;
}

Color SpotLight::cast(const Vector& target) const {
//    float x = max((target - getPosition()).dot(getOrientationEuler()), 0.0f);
    float x = 1.0;
    return color * x * size;
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

