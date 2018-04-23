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

class Light : Element {
    Color color = Colors::WHITE;
    double intensity = 1.;
};

class PointLight : public Light {};

class AreaLight : public Light {};

class SpotLight : public Light {};

class AmbientLight : public Light {};



#endif /* light_hpp */
