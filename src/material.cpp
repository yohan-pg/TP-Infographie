//
//  material.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//
#include "scene.hpp"


/* Fonctions de reflect/refract/fresnel basées sur:
   https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel */

//Vector reflect(const Vector& ingoing, const Vector& normal) {
//    return ingoing - 2 * ingoing.dot(normal) * normal;
//}
//
//Vector refract(const Vector &ingoing, const Vector normal, const float ior) {
//    float cosi = max(-1, min(1, ingoing.dot(normal));
//    float etai = 1, etat = ior;
//    Vector n = normal;
//    if (cosi < 0) { cosi = -cosi; } else { std::swap(etai, etat); n = -normal; }
//    float eta = etai / etat;
//    float k = 1 - eta * eta * (1 - cosi * cosi);
//    return k < 0 ? 0 : eta * ingoing + (eta * cosi - sqrtf(k)) * n;
//}
//
//float fresnel(const Vector &ingoing, const Vector &normal, const float &ior)
//{
//    float cosi = clamp(-1, 1, ingoing.dot(normal));
//    float etai = 1, etat = ior;
//    if (cosi > 0) { std::swap(etai, etat); }
//    
//    // Compute sini using Snell's law
//    float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
//    
//    // Total internal reflection
//    if (sint >= 1) {
//        kr = 1;
//    }
//    else {
//        float cost = sqrtf(std::max(0.f, 1 - sint * sint));
//        cosi = fabsf(cosi);
//        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
//        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
//        kr = (Rs * Rs + Rp * Rp) / 2;
//    }
//    return kr;
//}
//                     
//Vector sample_hemisphere(const float &r1, const float &r2)
//{
//    float sinTheta = sqrtf(1 - r1 * r1);
//    float phi = 2 * M_PI * r2;
//    float x = sinTheta * cosf(phi);
//    float z = sinTheta * sinf(phi);
//    return Vector(x, u1, z);
//}

/* Fin fonctions vendor */
//
//
//Color Material::shade(const Collision& coll, int depth) {
//    Color color;
//    const Vector& ingoing = coll.ray.direction;
//    
//    /* Diffuse Term */
//    
//    color += diffuse;
//    
//    /* Emissivity Term */
//    
//    color += albedo * emissivity;

//    /* Specular Highlight Term */
//

//    /* Paramteric Light Contribution */
//    
//    for (int i = 0; i < scene.lights.size(); i++) {
//        color += scene.lights[i].cast(coll.position);
//    }
//    
//    /* Metalness/Transmission Term */
//    
//    if (metalness > 0) {
//        Color reflectionColor = scene.trace(reflect(ingoing, coll.normal), depth-1);
//        Color refractionColor = scene.trace(refract(ingoing, coll.normal, ior), depth-1);
//        
//        float kr = fresnel();
//        
//        color += metalness * (reflectionColor * kr + refractionColor * (1 - kr));
//    }
//    
//    /* Indirect Term */
//    
//    std::default_random_engine generator;
//    std::uniform_real_distribution<float> distribution(0, 1);
//    
//    Color ambientColor;
//    for (int i = 0; i < scene.ambient_samples; i++) {
//        Vector outgoing = sample_hemisphere(distribution(generator), distribution(generator);
//        ambientColor += scene.trace(Ray(coll.position, outgoing);
//    }
//    color += ambientColor = scene.ambient_samples;
//    
//
//    /* Add in ambient */
//   return diffuseColor + ambientColor + lightColor
//}
//                                    






