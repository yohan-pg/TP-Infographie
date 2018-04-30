//
//  scene..hpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#pragma once

#ifndef scene_hpp
#define scene_hpp

#include <stdio.h>
#include "ofMain.h"
#include "shape.hpp"
#include "light.hpp"
#include "color.hpp"
#include "camera.hpp"
#include "film.hpp"
#include "element.hpp"
#include <iostream>
#include <mutex>

class Scene {
public:
    Color background = Color(1, 1, 1, 1.0);
    Color ambient = Color(0, 0, 0, 1.0);
    
    Element* selection;
    
    Camera camera;
    Film film;
    
    int tracingDepth = 4;
    
    vector<Element*> elements;
    vector<Shape*> shapes;
    vector<Light*> lights;
    
    void add(Shape* shape);
    void add(Light* light);
    void remove(Element* elem);
    void clear();
    
    void select(int x, int y);
    void select(Element* element);
    
    void draw() const;
    Color trace(const Ray& ray, int depth=1, Shape* ignore=NULL) const;
    Collision intersect(const Ray& ray, Shape* ignore=NULL) const;
    
//    mutex elementLock;
};

extern Scene scene;

#endif /* scene_hpp */
