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
    Collision hit;
    if (scene->intersect(Ray(pos, target - pos), hit)) {
        return Color::black;
    } else {
        return color * intensity;
    }
}

Color SpotLight::cast(const Vector& target) const {
    Vector pos = getPosition();
    Vector dir = getOrientationEuler();
    Collision hit;
    if (scene->intersect(Ray(pos, target - pos), hit)) {
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

