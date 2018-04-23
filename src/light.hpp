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
//#include "scene.hpp"

class Light : public Element {
    Color color = Color::white;
    double intensity = 1.;
    string getName();
//    Color cast(const Scene& scene, const Vector& pos) = 0;
};

class PointLight : public Light {
    string getName();
//    Color cast(const Scene& scene, const Vector& pos) const;
};

class SpotLight : public Light {
    float size;
    string getName();
//    Color cast(const Scene& scene, const Vector& pos) const;
};

class AmbientLight : public Light {
    string getName();
//    Color cast(const Scene& scene, const Vector& pos) const;
};



#endif /* light_hpp */
