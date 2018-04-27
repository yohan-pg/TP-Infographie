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
#include <boost/optional.hpp>

class Collision;

class Shape : public Element {
public:
    Material material;
    bool smooth = true;
    virtual string getName() const;
    virtual Collision* intersect(const Ray& ray);
    virtual void draw();
};

class Sphere : public Shape {
    ofSpherePrimitive primitive;
public:
    Sphere(float radis=1.0);
    float getRadius() const;
    string getName() const;
    virtual Collision* intersect(const Ray& ray);
    void draw();
};

class Plane : public Shape {
    ofPlanePrimitive primitive;
    Normal normal;
public:
    Plane();
    Plane(Normal normal);
    string getName() const;
    virtual Collision* intersect(const Ray& ray);
    void draw();
};

class Disk : public Shape {
    Normal normal;
    float radius;
public:
    float getRadius() const;
    Disk(Normal normal, float radius=1.0);
    string getName() const;
    virtual Collision* intersect(const Ray& ray);
};

class Box : public Shape {
public:
    string getName() const;
    virtual Collision* intersect(const Ray& ray);
};

class Bound : public Sphere {
    vector<Shape> items;
public:
    Bound(vector<Shape> items);
    virtual Collision* intersect(const Ray& ray);
};

class Triangle : public Shape {
    Normal normal;
    Vector left;
    Vector right;
public:
    Triangle(Vector a, Vector b, Vector c);
    string getName() const;
    virtual Collision* intersect(const Ray& ray);
};

class Mesh : public Shape {
public:
    vector<Triangle> triangles;
    string getName() const;
    virtual Collision* intersect(const Ray& ray);
};


extern Shape unit_shape;

#endif /* shape_hpp */
