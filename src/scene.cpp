//
//  scene.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "scene.hpp"
#include "gui.hpp"

Scene scene = Scene();

void Scene::add(Shape* shape) {
    shapes.push_back(shape);
    elements.push_back(shape);
}

void Scene::add(Light* light) {
    lights.push_back(light);
    elements.push_back(light);
}

void Scene::remove(Element* elem) {
    if (dynamic_cast<Shape*>(elem)) {
        shapes.erase(std::remove(shapes.begin(), shapes.end(), elem), shapes.end());
    }
    if (dynamic_cast<Light*>(elem)) {
        shapes.erase(std::remove(shapes.begin(), shapes.end(), elem), shapes.end());
    }
    elements.erase(std::remove(elements.begin(), elements.end(), elem), elements.end());
    delete elem;
}

void Scene::clear() {
    selection = NULL;
    lights.clear();
    shapes.clear();
    elements.clear();
    for (auto element : elements) {
        delete element;
    }    
}

void Scene::draw() const{
    for (int i = 0; i < elements.size(); i++) {
        elements[i]->draw();
    }
}

Collision Scene::intersect(const Ray& ray, Shape* ignore) const {
    float best = std::numeric_limits<float>::max();
    Collision result;
    for (int i = 0; i < shapes.size(); i++) {
        if (shapes[i] == ignore) continue;
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
    Ray ray = camera.primaryRay(film, x, y);
    for (auto light : lights) {
        if (light->intersect(ray)) {
            select(light);
            return;
        }
    }
    auto hit = intersect(ray);
    if (hit) {
        select(hit.shape);
    } else {
        selection = NULL;
    }
}

void Scene::select(Element* element) {
    selection = element;
    gui.updateSelection();
}

Color Scene::trace(const Ray& ray, int depth, Shape* ignore) const {
    if (depth > 0) {
        auto hit = intersect(ray, ignore);
        if (hit) {
            auto result = hit.shape->material.shade(ray, hit, depth);
            return result;
        }
    }
    return background;
}

