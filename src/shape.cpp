//
//  shape.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "shape.hpp"
#include "scene.hpp"
#include "collision.hpp"

Collision Shape::intersect(const Ray& ray) {
    return Missed;
}

void Shape::draw() {
    if (scene.selection == this) {
        ofSetColor(Color(1,1,1));
    }
    else {
        ofSetColor(material.albedo);
    }
}

Sphere::Sphere(float r) {
    radius = r;
    primitive.setRadius(r);
}

Collision Sphere::intersect(const Ray& ray) {
    float base = ray.direction.dot(ray.position);
    float discr = base * base - ray.position.dot(ray.position) + radius*radius;
    if (discr <= 0) return Missed;
    float root = sqrt(discr);
    float dist =  min(-base-root, -base+root);
    Vector hitpos = ray.at(dist) * getGlobalTransformMatrix();
    return Collision(ray, *this, hitpos, Normal(hitpos-getPosition()));
}

void Sphere::draw() {
    Shape::draw();
    primitive.setTransformMatrix(getGlobalTransformMatrix());
    primitive.drawWireframe();
}

Plane::Plane(Normal normal) : normal(normal) {}

float planar_distance(const Ray& ray, const Normal& normal) {
    float denom = ray.direction.dot(-normal);
    bool is_parallel = denom < 1e-5;
    if (is_parallel) return -1;
    float num = ( - ray.position).dot(-normal);
    float dist = num / denom;
    if (num < 0) return -1;
    return dist;
}

Collision Plane::intersect(const Ray& ray) {
    float dist = planar_distance(ray,  normal);
    if (dist > 0) {
        return Collision(ray, *this, ray.at(dist) * getGlobalTransformMatrix(), normal);
    }
    return Missed;
}

void Plane::draw() {
    Shape::draw();
    primitive.setTransformMatrix(getGlobalTransformMatrix());
    primitive.drawWireframe();
}

Disk::Disk(Normal normal, float radius) : normal(normal), radius(radius) {}

float Disk::getRadius() const {
    return radius;
}

Collision Disk::intersect(const Ray& ray) {
    float dist = planar_distance(ray, normal);
    Vector hitpos = ray.at(dist);
    if (dist > 0 && (getPosition() - hitpos).length() < 10) {
        return Collision(ray, *this, hitpos * getGlobalTransformMatrix(), normal);
    }
    return Missed;
}

void Disk::draw() {
    primitive.draw();
}

Collision Box::intersect(const Ray& ray) {
    Vector d = ray.direction;
    Vector p = ray.position;
    float idx = -1.0 / d.x;
    float idy = -1.0 / d.y;
    float idz = -1.0 / d.z;
    float r = 0.5f;
    vector<float> intersections = {
        (r - p.x) / idx,
        (r + p.x) / idx,
        (r - p.y) / idy,
        (r + p.y) / idy,
        (r - p.z) / idz,
        (r + p.z) / idz
    };
    for (auto i : intersections) {
        Vector p = ray.at(i);
        if (abs(p.x) < r && abs(p.y) < r && abs(p.z) < r) {
            return Collision(ray, *this, p * getGlobalTransformMatrix(), Vector(0,0,0));
        }
    }
   return Missed;
}

Triangle::Triangle(Vector a, Vector b, Vector c) : a(a), b(b), c(c), normal((b-a).cross(c-a).normalize()) {
    setPosition(a);
}

Triangle::Triangle(Vector a, Vector b, Vector c, Vector normal) : a(a), b(b), c(c), normal(normal) {
    setPosition(a);
}


inline float intersect_triangle(const Ray& ray, Vector a, Vector b, Vector c, Vector normal) {
    float dist = planar_distance(Ray(ray.position+a, ray.direction), normal);
    if (dist < 0) return -1;
    Vector hitpos = ray.at(dist);
    if ((b-a).cross(hitpos - a).dot(normal) < 0) return -1;
    if ((c-b).cross(hitpos - b).dot(normal) < 0) return -1;
    if ((a-c).cross(hitpos - c).dot(normal) < 0) return -1;
    return dist;
    return -1;
}

Collision Triangle::intersect(const Ray& ray) {
    float dist = intersect_triangle(ray, a, b, c, normal);
    if (dist >= 0) {
        return Collision(ray, *this, ray.at(dist) * getGlobalTransformMatrix(), normal);
    }
    return Missed;
}

void Mesh::add(Triangle* triangle) {
    triangles.push_back(triangle);
}

Collision Mesh::intersect(const Ray& ray) {
    float best = std::numeric_limits<float>::max();
    Collision result;
    for (auto tri : triangles) {
        Collision hit = tri->intersect(ray);
        float dist = (hit.position - ray.position).lengthSquared();
        if (hit && (dist < best)) {
            best = dist;
            result = hit;
        }
    }
    return result;
}

MeshConverter::MeshConverter(ofMesh mesh) : mesh(mesh) {}

Collision MeshConverter::intersect(const Ray& ray) {
    float best = std::numeric_limits<float>::max();
    Collision choice;
//    for (auto face : mesh.getFace(0)) {
//        auto face = mesh.getFace(1);
//        Vector a = face.getVertex(0);
//        Vector b = face.getVertex(1);
//        Vector c = face.getVertex(2);
//        Vector left = b - a;
//        Vector right = c - a;
//        Normal normal = face.getFaceNormal();
//        float dist = intersect_triangle(ray, a, left, right, normal);
//        if (dist >= 0) {
//            return Collision(ray, *this, ray.at(dist) * getGlobalTransformMatrix(), normal);
//        }
//    }
    return choice;
}

string Shape::getName() const {
    return "Shape";
}

string Plane::getName() const{
    return "Plane";
}

string Disk::getName() const{
    return "Disk";
}

string Box::getName() const{
    return "Box";
}

string Sphere::getName() const{
    return "Sphere";
}

string Triangle::getName() const{
    return "Triangle";
}

string Mesh::getName() const{
    return "Mesh";
}
