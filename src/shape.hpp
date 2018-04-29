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
    virtual Collision intersect(const Ray& ray);
};

class Mesh : public Shape {
public:
    vector<Triangle*> triangles;
    string getName() const;
    void add(Triangle* triangle);
    virtual Collision intersect(const Ray& ray);
};

class MeshConverter : public Shape {
public:
    ofMesh mesh;
    MeshConverter(ofMesh mesh);
    string getName() const;
    Collision intersect(const Ray& ray);
};


#endif /* shape_hpp */
