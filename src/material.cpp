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



Vector reflect(const Vector& ingoing, const Vector& normal) {
    return ingoing - 2 * normal.dot(ingoing) * normal;
}

Vector refract2(const Vector& ingoing, const Vector& normal, float ior_in, float ior_out) {
    float ratio = ior_in / ior_out;
    float ni = normal.dot(ingoing);
    float k = 1.0 - ior_in * ior_in * (1.0 - ni * ni);
//    if (k < 0) fail
    return ratio * ingoing - (ratio * ni + sqrtf(k) * normal);
}

/* Fonctions de reflect/refract/fresnel bases sur:
   https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel */

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


Color Material::shade(const Ray& ray, const Collision& hit, int depth) const {
    Color color = Color(0, 0, 0);
    const Vector& view_vector = (ray.position - hit.position).getNormalized();
    
     for (int i = 0; i < scene.lights.size(); i++) {
         
            Vector ingoing_vector = (hit.position - scene.lights[i]->getPosition()).normalize();
            Vector light_vector = -ingoing_vector;
         
            Color lighting = scene.lights[i]->cast(hit.position, light_vector, hit.normal);
            color += lighting * albedo;
         
            if (scene.lights[i]->isSpecular()) {
                Vector specular_vector = Vector(0,0,0);
                switch (shadertype) {
                    case ShaderType::LAMBERT:
                        break;
                    case ShaderType::BLINN:
                        specular_vector = (view_vector + light_vector).normalize();
                        break;
                    case ShaderType::PHONG:
                        specular_vector = reflect(ingoing_vector, hit.normal);
                        break;
                }
                float factor = shadertype == ShaderType::BLINN ? 10.0 : 1.0;
                
                color += specularAmount * pow(ofClamp(specular_vector.dot(view_vector), -5*sheen, 1), specularHardness * factor);
            }
    }

//    if (reflection > 0) {
//        Vector reflection_vector = reflect(ray.direction, hit.normal);
//        Ray reflectionRay = Ray(hit.position, reflect(ray.direction, hit.normal));
//        color = color * (1-reflection) + scene.trace(reflectionRay, depth-1) * reflection;
//    }

//    if (refraction > 0) {
//        Vector reflection_vector = reflect(ray.direction, hit.normal);
//        Ray reflectionRay = Ray(hit.position, reflect(ray.direction, hit.normal));
//        color = color * (1-reflection) + scene.trace(reflectionRay, depth-1) * reflection;
//    }

  
    return color;
}
                                    






