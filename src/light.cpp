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
    setPosition(Vector(i++, 1, 2));
}

bool Light::isSpecular() {
    return true;
}

Color Light::cast(const Vector& target, Vector light_vector, Normal normal) const {
    float distance = (target - getPosition()).length();
    Color result = Color(0,0,0);
    for (int i = 0; i < shadowSamples; i++) {
        Vector pos = getPosition();
        if (shadowSamples > 1) {
            pos += Sampler::sphere_vector().normalize() * size;
        }
        Ray ray = Ray(pos, target);
        Collision hit = scene.intersect(ray);
        if (!hit || !((hit.position - pos).length() < (distance - 0.001))) {
            result += color * (1.0/(float)shadowSamples);
        }
    }
    float falloff = 1 / (attentuation * distance);
    float cosine = normal.dot(light_vector);
    return result * intensity * falloff * cosine;
    
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

bool Light::intersect(const Ray & ray) {
    return intersect_sphere(ray * getGlobalTransformMatrix().getInverse(), 0.1) > 0;
}

Color SpotLight::cast(const Vector& target, Vector light_vector, Normal normal) const {
    float cone = pow(max(-light_vector.dot(direction), 0.0f), 1);
    return Light::cast(target, light_vector, normal) * cone;
}

void SpotLight::draw() {
    ofSetColor(255,200,0);
    if (scene.selection == this) {
        ofSetColor(255,255,255);
    }
    primitive.setPosition(getPosition());
    primitive.draw();
    ofSetColor(255,255,255);
}

Color DirectionalLight::cast(const Vector& target, Vector light_vector, Normal normal) const {
    float directionality = -light_vector.dot(normal);
    return Light::cast(target, light_vector, normal) * directionality;
}

void DirectionalLight::draw() {
    ofSetColor(255,150,0);
    if (scene.selection == this) {
        ofSetColor(255,255,255);
    }
    primitive.setPosition(getPosition());
    primitive.draw();
    ofSetColor(255,255,255);
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

