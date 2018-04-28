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
    virtual Collision intersect(const Ray& ray);
    virtual void draw();
};

class Sphere : public Shape {
    ofSpherePrimitive primitive;
    float radius;
public:
    Sphere(float radius=1.0);
    float getRadius() const;
    string getName() const;
    virtual Collision intersect(const Ray& ray);
    void draw();
};

class Plane : public Shape {
    ofPlanePrimitive primitive;
    Normal normal;
public:
    Plane();
    Plane(Normal normal);
    string getName() const;
    virtual Collision intersect(const Ray& ray);
    void draw();
};

class Disk : public Shape {
    ofPlanePrimitive primitive;
    Normal normal;
    float radius;
public:
    float getRadius() const;
    Disk(Normal normal, float radius=1.0);
    string getName() const;
    virtual Collision intersect(const Ray& ray);
    void draw();
};

class Box : public Shape {
    ofPlanePrimitive primitive;
public:
    string getName() const;
    virtual Collision intersect(const Ray& ray);
    void draw();
};

class Bound : public Sphere {
    vector<Shape> items;
public:
    Bound(vector<Shape> items);
    virtual Collision intersect(const Ray& ray);
};

class Triangle : public Shape {
    Normal normal;
    Vector left;
    Vector right;
public:
    Triangle(Vector a, Vector b, Vector c);
    string getName() const;
    virtual Collision intersect(const Ray& ray);
};

class Mesh : public Shape {
    
public:
    ofMesh mesh;
    Mesh(ofMesh mesh);
    string getName() const;
    Collision intersect(const Ray& ray);
};


extern Shape unit_shape;

#endif /* shape_hpp */
