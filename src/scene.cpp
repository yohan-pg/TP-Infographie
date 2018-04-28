//
//  scene.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "scene.hpp"

Scene scene = Scene();

void Scene::add(Shape* shape) {
    shapes.push_back(shape);
    elements.push_back(shape);
}

void Scene::add(Light* light) {
    lights.push_back(light);
    elements.push_back(light);
}

bool Scene::remove(Shape* shape) {
    return false; 
}

bool Scene::remove(Light* light) {
    return false;
}

void Scene::draw() const{
    for (int i = 0; i < elements.size(); i++) {
        elements[i]->draw();
    }
}

Collision Scene::intersect(const Ray& ray) const {
    float best = std::numeric_limits<float>::max();
    Collision result;
    for (int i = 0; i < shapes.size(); i++) {
        auto candidate = shapes[i]->intersect(ray * shapes[i]->getGlobalTransformMatrix().getInverse());
        if (candidate) {
            float dist = (candidate.position - candidate.ray->position).lengthSquared();
            if (dist < best) {
                result = candidate;
                best = dist;
            }
        }
    }
    return result;
}

void Scene::select(int x, int y) {
    auto hit = intersect(camera.primaryRay(film, x, y));
    if (hit) {
        selection = hit.shape;
    } else {
        selection = NULL;
    }
}

void Scene::select(Element* element) {
    selection = element;
}

Color Scene::trace(const Ray& ray, int depth) const {
    if (depth > 0) {
        auto hit = intersect(ray);
        if (hit) {
            auto result = hit.shape->material.shade(ray, hit, depth);
            return result;
        }
    }
    return background;
}

