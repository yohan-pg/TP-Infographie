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

class Scene {
public:
    vector<Shape> shapes;
    vector<Light> lights;
    
    void add(const Shape& shape);
    void add(const Light& light);
    bool remove(const Light& light);
    bool remove(const Shape& shape);
    
    void draw() const;
    Color trace(const Ray& ray) const;
};

#endif /* scene_hpp */
