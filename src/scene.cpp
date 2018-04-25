//
//  scene.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "scene.hpp"

Scene* scene = new Scene();

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

void Scene::draw() {
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i]->draw();
    }
}

bool Scene::intersect(const Ray& ray, Collision& hit) const {
    float best = std::numeric_limits<float>::max();
    bool result = false;
    for (int i = 0; i < shapes.size(); i++) {
        Collision coll;
        bool b = shapes[i]->intersect(ray * shapes[i]->getGlobalTransformMatrix().getInverse(), coll);
        if (b && coll.distance < best) {
            result = true;
            best = coll.distance;
            hit = coll;
        }
    }
    return result;
}

void Scene::select(int x, int y) {
    Collision coll;
    if (intersect(camera.primaryRay(film, x, y), coll)) {
//        selection = coll.shape;
    }
}

Color Scene::trace(const Ray& ray, int depth) const {
    if (depth > 0) {
        Collision hit;
        if (intersect(ray, hit)) {
            return hit.shape.material.shade(hit, depth);
        }
    }
    return background;
}

