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
    void draw() const;
    string getName();
    virtual Collision intersect(const Ray& ray) const;
};

class Sphere : public Shape {
public:
    double radius() const;
    void draw() const;
    string getName();
    Collision intersect(const Ray& ray) const;
};

class Plane : public Shape {
    Normal normal;
    Vector origin;
public:
    void draw() const;
    string getName();
    Collision intersect(const Ray& ray) const;
};

class Disk : public Shape {
    Normal normal;
    Vector origin;
    float radius;
public:
    void draw() const;
    string getName();
    Collision intersect(const Ray& ray) const;
};

class Box : public Shape {
public:
    void draw() const;
    string getName();
    Collision intersect(const Ray& ray) const;
};

class Triangle : public Shape {
    Normal normal;
    Vector a;
    Vector b;
    Vector c;
public:
    string getName();
    Collision intersect(const Ray& ray) const;
};

class Mesh : public Shape {
    vector<Triangle> triangles;
public:
    void draw() const;
    string getName();
    Collision intersect(const Ray& ray) const;
};


class Collision {
public:
    bool hit = false;
    const Ray& ray;
    const Shape& shape;
    Vector position;
    Vector normal;
    float distance;
    Collision(const Ray& ray, const Shape& shape, Vector position, Vector normal, float distance);
};

//Collision Missed;


#endif /* shape_hpp */
