//
//  material.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "material.hpp"
#include "scene.hpp"
#include "collision.hpp"

using namespace std;

/* Fonctions de reflect/refract/fresnel bases sur:
   https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel */

Vector reflect(const Vector& ingoing, const Vector& normal) {
    return ingoing - 2 * ingoing.dot(normal) * normal;
}

Vector refract(const Vector &ingoing, const Vector normal, const float ior) {
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
//    return k < 0.0f ? Vector() : eta * ingoing + (eta * cosi - sqrtf(k)) * n;
    // ignore total internal reflection for now
    return (eta * cosi - sqrtf(k)) * n;
}
    
float fresnel(const Vector &ingoing, const Vector &normal, const float &ior)
{
    float kr;
    float cosi = max(-1.0f, min(1.0f, ingoing.dot(normal)));
    float etai = 1, etat = ior;
    if (cosi > 0) { swap(etai, etat); }
    
    // Compute sini using Snell's law
    float sint = etai / etat * sqrtf(max(0.f, 1 - cosi * cosi));
    
    // Total internal reflection
    if (sint >= 1) {
        return 1;
    }
    else {
        float cost = sqrtf(std::max(0.f, 1 - sint * sint));
        cosi = fabsf(cosi);
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
        return (Rs * Rs + Rp * Rp) / 2;
    }
}
/* Fin fonctions vendor */

Color Material::shade(const Collision& hit, int depth) const {
    Color color = Color(0, 0, 0);
    const Vector& ingoing = hit.ray.direction;
    
    /* Diffuse Term */
    color += diffuse;
    
//    color = color + albedo;
    
    /* Paramteric Light Contribution */
    for (int i = 0; i < scene->lights.size(); i++) {
        Color lighting = scene->lights[i]->cast(hit.position);
        
        /* Diffuse Term */
        Vector dir = scene->lights[i]->getPosition() - hit.position;
        float cos = hit.normal.dot(dir);
        color += lighting * cos * albedo ; // add in cos normal
        
        /* Specular Highlight Term */
        
//        color += lighting *
    }
    
    
    /* Emissivity Term */
//    color += albedo * emissivity;
    
    return color;

    /* Metalness/Transmission Term */
    
//    Color reflectionColor = scene->trace(reflect(ingoing, hit.normal), depth-1);
//    Color refractionColor = scene->trace(refract(ingoing, hit.normal, ior), depth-1);
//
//    float reflection = fresnel();
//    float refraction = 1-reflection;
//
//    color += reflectionColor * reflected + refractionColor * refraction;
//    
//    /* Indirect Term */
//    
////
////    Color ambientColor;
////    for (int i = 0; i < scene.ambient_samples; i++) {
////        Vector outgoing = sample_hemisphere(distribution(generator), distribution(generator);
////        ambientColor += scene.trace(Ray(coll.position, outgoing);
////    }
//    color += ambientColor = scene.ambient_samples;
    

   /* Final mix */
//   return diffuseColor + ambientColor + lightColor
}
                                    






