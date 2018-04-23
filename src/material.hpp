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


class Material {
    ofColor albedo;
    float metalness = 0;
    float emmisivity = 0;
    float roughness = 0;
    float transmission = 0;
    float anisotropy = 0;
    float ior = 1.5;
    
    virtual float brdf(Vector normal, Vector ingoing, Vector outgoing);
    virtual float bsdf(Vector normal, Vector ingoing, Vector outgoing);
};

class Lambert : public Material {
    float brdf(Vector normal, Vector ingoing, Vector outgoing);
    float bsdf(Vector normal, Vector ingoing, Vector outgoing);
};

class Phong : public Material {
    float brdf(Vector normal, Vector ingoing, Vector outgoing);
    float bsdf(Vector normal, Vector ingoing, Vector outgoing);
};

class Blin : public Material {
    float brdf(Vector normal, Vector ingoing, Vector outgoing);
    float bsdf(Vector normal, Vector ingoing, Vector outgoing);
};

class Mirror : public Material {
    float brdf(Vector normal, Vector ingoing, Vector outgoing);
    float bsdf(Vector normal, Vector ingoing, Vector outgoing);
};

class Ward : public Material {
    float brdf(Vector normal, Vector ingoing, Vector outgoing);
    float bsdf(Vector normal, Vector ingoing, Vector outgoing);
};

class OrenNayar : public Material {
    float brdf(Vector normal, Vector ingoing, Vector outgoing);
    float bsdf(Vector normal, Vector ingoing, Vector outgoing);
};

class GGX : public Material {
    float brdf(Vector normal, Vector ingoing, Vector outgoing);
    float bsdf(Vector normal, Vector ingoing, Vector outgoing);
};

class AshikhminShirley : public Material {
    float brdf(Vector normal, Vector ingoing, Vector outgoing);
    float bsdf(Vector normal, Vector ingoing, Vector outgoing);
};




#endif /* material_hpp */
