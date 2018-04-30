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

Vector reflect(const Vector& ingoing, const Normal& normal) {
    return ingoing - 2 * normal.dot(ingoing) * normal;
}

const float inv_pi = 1/3.1416;
float Material::brdf(Normal normal, Vector ingoing, Vector outgoing) const {
    return inv_pi * normal.dot(-ingoing);
}

Color Material::shade(const Ray& ray, const Collision& hit, int depth) const {
    Color color = Color(0, 0, 0);
    Color specularColor = Color(0, 0, 0);
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
                specularColor += lighting * specularAmount
                                          * pow(ofClamp(specular_vector.dot(view_vector), 0, 1), specularHardness * factor);
            }
    }

    float reflectivity = fresnel(ray.direction, hit.normal, ior);
    float refractivity = 1 - reflectivity;
    
    if (reflection > 0) {
        Ray reflectionRay = Ray(hit.position, reflect(ray.direction, hit.normal));
        float blend = (1 - reflectivity * (1 - transmission)) * reflection;
        color = scene.trace(reflectionRay, depth-1, hit.shape) * blend;
    }

    if (refraction > 0) {
        float blend = refractivity * refraction;
        color = color * (1.0f - blend) + scene.trace(Ray(hit.position, refract(ray.direction, hit.normal, ior)), depth-1, hit.shape) * blend;
    }
    
    Color globalIllum = Color(0, 0, 0);
    if (ambient > 0) {
        for (int i = 0; i < indirectBounces; i++) {
            Ray ambientRay = Ray(hit.position, Sampler::sphere_vector());
            globalIllum += scene.trace(ambientRay, depth-1, hit.shape)
            * (1.0 / (float)indirectBounces)
            * brdf(hit.normal, ray.direction, ambientRay.direction);
        }
    }
    
    return color
         + specularColor * (1 - refraction) * (1 - reflection)
         + scene.ambient
         + globalIllum * ambient ;
}






