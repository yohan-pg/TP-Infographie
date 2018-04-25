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
#include <limits>

class Collision;

class Shape : public Element {
public:
    Material material;
    bool smooth = true;
    virtual string getName() const;
    virtual bool intersect(const Ray& ray, Collision& hit) const;
    virtual void draw();
};

class Sphere : public Shape {
    ofSpherePrimitive primitive;
public:
    Sphere(float radis=1.0);
    float getRadius() const;
    string getName() const;
    bool intersect(const Ray& ray, Collision& hit) const;
    void draw();
};

class Plane : public Shape {
    Normal normal;
public:
    Plane(Normal normal);
    string getName() const;
    bool intersect(const Ray& ray, Collision& hit) const;
};

class Disk : public Shape {
    Normal normal;
    float radius;
public:
    float getRadius() const;
    Disk(Normal normal, float radius);
    string getName() const;
    bool intersect(const Ray& ray, Collision& hit) const;
};

class Box : public Shape {
public:
    string getName() const;
    bool intersect(const Ray& ray, Collision& hit) const;
};

class Triangle : public Shape {
    Normal normal;
    Vector left;
    Vector right;
public:
    Triangle(Vector a, Vector b, Vector c);
    string getName() const;
    bool intersect(const Ray& ray, Collision& hit) const;
};

class Mesh : public Shape {
public:
    vector<Triangle> triangles;
    string getName() const;
    bool intersect(const Ray& ray, Collision& hit) const;
};


extern Shape unit_shape;

#endif /* shape_hpp */
