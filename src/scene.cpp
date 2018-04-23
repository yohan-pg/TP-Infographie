//
//  scene.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "scene.hpp"

Scene scene;

void Scene::add(Shape* shape) {
    shapes.push_back(shape);
    elements.push_back(shape);
}

void Scene::add(Light* light) {
    lights.push_back(light);
    elements.push_back(light);
}

bool Scene::remove(Shape* shape) {
    return false; //todo
}

bool Scene::remove(Light* light) {
    return false; //todo
}

void Scene::draw() const {
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i]->draw();
    }
}

Collision Scene::intersect(const Ray& ray) const {
//    Collision best = Missed;
//    float bestDist = Missed.distance;
//    for (int i = 0; i < shapes.size(); i++) {
//        auto hit = shapes[i].intersect(ray);
//        if (hit.distance < bestDist) {
////            best = hit;
//            bestDist = hit.distance;
//        }
//    }
}

Color Scene::trace(const Ray& ray, int depth) const {
    if (depth > 0) {
        auto coll = intersect(ray);
        if (coll.hit) {
//            return coll.shape.material.shade(this, coll, depth-1);
        }
    }
    return ambient;
}

