//
//  material.hpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#ifndef material_hpp
#define material_hpp

#include <stdio.h>
#include "ofMain.h"
#include "vector.hpp"
#include "color.hpp"
#include <math.h>

class Collision;

class Material {
public:
    Color albedo = Color::red;
    Color diffuse = Color::black;
    Color specularTint = Color::white;
    float metalness = 0;
    float emissivity = 0;
    float roughness = 0;
    float transmission = 0;
    float anisotropy = 0;
    float specular = 0;
    float clearcoat = 0;
    float sheen = 0;
    float sheenTint = 0;
    float ior = 1.5;
    Color shade(const Collision& hit, int depth) const;
    float brdf(Vector normal, Vector ingoing, Vector outgoing);
    float bsdf(Vector normal, Vector ingoing, Vector outgoing);
};

class Lambert : public Material {
    Color albedo = Color::darkorange;
};

class Blinn : public Material {
    Color albedo = Color::darkCyan;
    float specular = 1;
};

class Plastic : public Material {
    Color albedo = Color::darkRed;
    float roughness = 0.4;
};

class Metal : public Material {
    float metalness = 1;
    float roughness = 0.8;
};

class Mirror : public Material {
    float metalness = 1;
};

class Glass : public Material {
    float ior = 1.4;
    float transmission = 1;
};



#endif /* material_hpp */
