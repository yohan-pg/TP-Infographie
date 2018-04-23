//
//  light.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "light.hpp"

//Color PointLight::cast(const Scene& scene, const Vector& target) {
//    Vector pos = getPosition();
//    Collision coll = scene.trace(Ray(pos, target - pos));
//    if (coll.hit) {
//        return color * intensity;
//    }
//    return scene.ambient;
//}
//
//Color SpotLight::cast(const Scene& scene, const Vector& target) const {
//    return color * max((target - getPosition()).dot(getGlobalOrientation()), 0) * tightness;
//}
//
////(max(L•S,0))m
//
//Color AmbientLight::cast(const Scene& scene, const Vector& target) const {
//    return color * intensity;
//}




string Light::getName() {
    return "Light";
}

string PointLight::getName() {
    return "PointLight";
}

string SpotLight::getName() {
    return "SpotLight";
}

string AmbientLight::getName() {
    return "AmbientLight";
}

