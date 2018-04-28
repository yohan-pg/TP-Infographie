//
//  light.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "light.hpp"
#include "scene.hpp"


float i = 0.0;

Light::Light() {
    primitive.setRadius(0.1);
    setPosition(Vector(i++, 3, 1));
}

bool Light::isSpecular() {
    return true;
}

Color Light::cast(const Vector& target, Vector light_vector, Normal normal) const {
    Vector pos = getPosition();
    Ray ray = Ray(pos, target);
    Collision hit = scene.intersect(ray);
    float distance = (target - pos).length();
    if (hit && ((hit.position - pos).length() < (distance - 0.001))) {
        return Color::black;
    } else {
        float falloff = 1 / (attentuation * distance); 
        float cosine = normal.dot(light_vector);
        return color * intensity * falloff * cosine;
    }
}

void Light::draw() {
    ofSetColor(255,255,0);
    if (scene.selection == this) {
        ofSetColor(255,255,255);
    }
    primitive.setPosition(getPosition());
    primitive.draw();
    ofSetColor(255,255,255);
}

Color SpotLight::cast(const Vector& target, Vector light_vector, Normal normal) const {
    float cone = -light_vector.dot(direction);
    return Light::cast(target, light_vector, normal) * cone;
}

Color DirectionalLight::cast(const Vector& target, Vector light_vector, Normal normal) const {
    float cosine = normal.dot(light_vector);
    float directionality = light_vector.dot(normal);
    return Light::cast(target, light_vector, normal) * cosine * directionality;
}

bool DirectionalLight::isSpecular() {
    return false;
}

Color AmbientLight::cast(const Vector& target, Vector light_vector, Normal normal) const {
    return color * intensity;
}

bool AmbientLight::isSpecular() {
    return false;
}

void AmbientLight::draw() {
    // draw nothing for ambient lights
}

string Light::getName() const {
    return "Light";
}

string PointLight::getName() const {
    return "PointLight";
}

string SpotLight::getName() const {
    return "SpotLight";
}

string DirectionalLight::getName() const {
    return "DirectionalLight";
}

string AmbientLight::getName() const {
    return "AmbientLight";
}

