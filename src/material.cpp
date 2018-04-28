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


Color Material::shade(const Collision& hit, int depth) const {
    Color color = Color(0, 0, 0);
    const Vector& view_vector = (hit.ray->direction).getNormalized();
    
    /* Diffuse Term */
    color += diffuse;
    
    if (metalness > 0) {
        Ray reflectionRay = Ray(hit.position, reflect(view_vector, hit.normal));
    } else {
        /* Paramteric Light Contribution */
        for (int i = 0; i < scene.lights.size(); i++) {
            Color lighting = scene.lights[i]->cast(hit.position, hit.ray->marked);
            Vector ingoing_vector = (scene.lights[i]->getPosition() - hit.position).normalize();
            float cos = hit.normal.dot(ingoing_vector);
            color += lighting * albedo * cos;
            Vector reflection_vector = reflect(ingoing_vector, hit.normal);
            color += reflection_vector.dot(view_vector);
            cout << endl;
            cout << "ingoing vector " << ingoing_vector << endl;
            cout << "view vector " << view_vector << endl;
            cout << "reflection vector " << reflection_vector << endl;
        }
    }
    
//    float reflected = fresnel(ingoing, hit.normal, ior);
//    Ray reflectionRay = Ray(hit.position, reflect(ingoing, hit.normal));
//    Color reflectionColor = scene.trace(reflectionRay, depth-1);
//    
//    float refracted = 1 - reflected;
//    Ray refractionRay = Ray(hit.position, refract(ingoing, hit.normal, ior));
//    Color refractionColor = scene.trace(refractionRay, depth-1);

//  Vector outgoing = sample_hemisphere(distribution(generator), distribution(generator);
//  reflectionColor * reflected + refractionColor * refraction;
    return color;

    /* Metalness/Transmission Term */

   /* Final mix */
//   return diffuseColor + ambientColor + lightColor
}
                                    






