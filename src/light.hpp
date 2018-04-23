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

class Light : public Element {
public:
    Color color = Color::white;
    double intensity = 1.0;
    string getName() const;
    virtual Color cast(const Vector& pos) const = 0;
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
