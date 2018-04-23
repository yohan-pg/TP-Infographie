//
//  shape.hpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#ifndef shape_hpp
#define shape_hpp

#include "ofMain.h"
#include <stdio.h>
#include "element.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "vector.hpp"

class Collision;

class Shape : public Element {
public:
    Material material;
    void draw() const;
    void intersect(const Ray& ray, bool hit, Vector& point) const;
};

class Sphere : public Shape {
public:
    double radius() const;
    void draw() const;
    void intersect(const Ray& ray, bool hit, Vector& point) const;
};

class Plane : public Shape {
public:
    void draw() const;
    void intersect(const Ray& ray, bool hit, Vector& point) const;
};

class Box : public Shape {
public:
    void draw() const;
    void intersect(const Ray& ray, bool hit, Vector& point) const;
};

class Triangle : public Shape {
public:
    void intersect(const Ray& ray, bool hit, Vector& point) const;
};

class Mesh : public Shape {
    vector<Triangle> triangles;
public:
    void draw() const;
    void intersect(const Ray& ray, bool hit, Vector& point) const;
};


class Collision {
    bool hit = false;
    Collision(const Ray& ray, Shape shape, Vector position);
};



#endif /* shape_hpp */