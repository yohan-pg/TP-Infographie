//
//  material.hpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#pragma once

#ifndef material_hpp
#define material_hpp

#include <stdio.h>
#include <math.h>
#include "ofMain.h"
#include "vector.hpp"
#include "color.hpp"
#include "ray.hpp"
#include "vendor.hpp"

class Collision;

enum ShaderType {
    LAMBERT = 1,
    BLINN = 2,
    PHONG = 3,
};

class Material {
public:
    ShaderType shadertype = ShaderType::PHONG;
    Color albedo = Color(0.7,0.5,0);
    float specularAmount = 0.8;
    float specularHardness = 4.0;
    float sheen = 0;
    float ior = 1.5;
    float reflection = 0;
    float refraction = 0;
    float transmission = 1.0;
    float ambient = 0.5;
    int indirectBounces = 3;
    
    Color shade(const Ray& ray, const Collision& hit, int depth) const;

    float brdf(Normal normal, Vector ingoing, Vector outgoing) const;
};

class Lambert : public Material {
    ShaderType shadertype = ShaderType::LAMBERT;
};

class Phong : public Material {
    ShaderType shadertype = ShaderType::PHONG;
    float roughness = 0.4;
};

class Blinn : public Material {
    ShaderType shadertype = ShaderType::BLINN;
    float roughness = 0.4;
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
