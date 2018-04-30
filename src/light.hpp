//
//  light.hpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#pragma once

#ifndef light_hpp
#define light_hpp

#include <stdio.h>
#include "ofMain.h"
#include "element.hpp"
#include "color.hpp"
#include "vector.hpp"
#include "collision.hpp"
#include "ray.hpp"

class Light : public Element {
protected:
    ofSpherePrimitive primitive;
public:
    Light();
    bool isSpecular();
    
    Color color = Color(1.0, 1.0, 1.0);
    float size = 1.0;
    int shadowSamples = 1;
    double intensity = 1.0;
    float attentuation = 0.1;
    
    bool intersect(const Ray & ray);
    
    string getName() const;
    virtual Color cast(const Vector& pos, Vector light_vector, Normal normal) const;
    virtual void draw();
};

class PointLight : public Light {
public:
    string getName() const;
};

class DirectionalLight : public Light {
public:
    bool isSpecular();
    Vector direction = Vector(-1, -1, 0);
    string getName() const;
    Color cast(const Vector& target, Vector light_vector, Normal normal) const;
    virtual void draw();
};

class SpotLight : public Light {
public:
    Vector direction = Vector(0, -1, 0);
    float size = 1.0;
    string getName() const;
    Color cast(const Vector& target, Vector light_vector, Normal normal) const;
    virtual void draw();
};

class AmbientLight : public Light {
public:
    bool isSpecular();
    string getName() const;
    Color cast(const Vector& target, Vector light_vector, Normal normal) const;
    virtual void draw();
};

#endif /* light_hpp */
