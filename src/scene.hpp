//
//  scene.hpp
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

class Scene {
public:
    Color background = Color(1, 1, 1);
    Color ambient = Color(0, 0, 0);
    
    const Shape* selection;
    
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
    
    void draw() ;
    Color trace(const Ray& ray, int depth=1) const;
    bool intersect(const Ray& ray, Collision& hit) const ;
};

extern Scene* scene;

#endif /* scene_hpp */
