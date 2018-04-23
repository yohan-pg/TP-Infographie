//
//  scene.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "scene.hpp"

void Scene::add(const Shape& shape) {
    shapes.push_back(shape);
}

void Scene::add(const Light& light) {
    lights.push_back(light);
}

bool Scene::remove(const Light& light) {
    return false;
}

bool Scene::remove(const Shape& shape) {
    return false;
}

void Scene::draw() const {
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].draw();
    }
}

Color Scene::trace(const Ray& ray) const {
    
//    for (int i = 0; i < shapes.size(); i++) {
//        
//    }
    return Colors::BLACK;
}

