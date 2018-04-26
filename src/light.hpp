//
//  light.hpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#ifndef light_hpp
#define light_hpp

#include <stdio.h>
#include "ofMain.h"
#include "element.hpp"
#include "color.hpp"
#include "vector.hpp"
#include "collision.hpp"

class Light : public Element {
    ofSpherePrimitive primitive;
public:
    Color color = Color(1.0, 1.0, 1.0);
    double intensity = 1.0;
    string getName() const;
    virtual Color cast(const Vector& pos) const;
    virtual void draw();
};

class PointLight : public Light {
public:
    string getName() const;
    Color cast(const Vector& target) const;
};

class SpotLight : public Light {
public:
    float size = 1.0;
    string getName() const;
    Color cast(const Vector& target) const;
};

class AmbientLight : public Light {
public:
    string getName() const;
    Color cast(const Vector& target) const;
};



#endif /* light_hpp */
