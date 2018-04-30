//
//  shape.hpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#pragma once

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
    Plane(Normal normal=Normal(0,1,0));
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

class Triangle : public Shape {
    Normal normal;
    Vector a;
    Vector b;
    Vector c;
public:
    Triangle(Vector a, Vector b, Vector c);
    Triangle(Vector a, Vector b, Vector c, Vector normal);
    string getName() const;
    float maxDist();
    virtual Collision intersect(const Ray& ray);
};

class Mesh : public Shape {
    float bound = 0;
    bool useBound;
public:
    vector<Triangle*> triangles;
    Mesh(vector<Triangle*> triangles);
    string getName() const;
    void computeBound();
    void add(Triangle* triangle);
    virtual Collision intersect(const Ray& ray);
};


#endif /* shape_hpp */
