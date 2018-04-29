//
//  vendor.cpp
//  GigaRay
//
//  Created by Yohan Poirier-Ginter on 2018-04-28.
//
//

#include <stdio.h>

#include "vector.hpp"

/* Fonctions de reflect/refract/fresnel bases sur:
 https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel */

Vector refract(const Vector &ingoing, Normal normal, float ior) {
    float cosi = max(-1.0f, min(1.0f, ingoing.dot(normal)));
    float etai = 1;
    float etat = ior;
    Vector n = normal;
    if (cosi < 0) {
        cosi = -cosi;
    } else {
        swap(etai, etat);
        n = -normal;
    }
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    //    k < 0.0f ? Vector() : eta * ingoing + (eta * cosi - sqrtf(k)) * n; // ignore total internal reflection for now
    return (eta * cosi - sqrtf(k)) * n;
}

float fresnel(const Vector &ingoing, Normal normal, float ior)
{
    float kr;
    float cosi = max(-1.0f, min(1.0f, ingoing.dot(normal)));
    float etai = 1, etat = ior;
    if (cosi > 0) { swap(etai, etat); }
    
    float sint = etai / etat * sqrtf(max(0.f, 1 - cosi * cosi));
    
    if (sint >= 1) {
        return 1;
    }
    else {
        float cost = sqrtf(max(0.f, 1 - sint * sint));
        cosi = fabsf(cosi);
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
        return (Rs * Rs + Rp * Rp) / 2;
    }
}

/* Fin fonctions vendor */
