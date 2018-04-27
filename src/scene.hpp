//
//  scene..hpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

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


class Scene {
public:
    Color background = Color(1, 1, 1);
    Color ambient = Color(0, 0, 0);
    
    Element* selection;
    
    Camera camera;
    Film film;
    
    int indirect_samples = 5;
    
    vector<Element*> elements;
    vector<Shape*> shapes;
    vector<Light*> lights;
    
    void add(Shape* shape);
    void add(Light* light);
    bool remove(Light* light);
    bool remove(Shape* shape);
    
    void select(int x, int y);
    void select(Element* element);
    
    void draw() const;
    Color trace(const Ray& ray, int depth=1) const;
    Collision intersect(const Ray& ray) const;
};

extern Scene scene;

#endif /* scene_hpp */
