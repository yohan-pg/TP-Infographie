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

boost::optional<Collision> Shape::intersect(const Ray& ray) {
    return boost::none;
}

void Shape::draw() {
    if (scene.selection == this) {
        ofSetColor(Color(1,1,1));
    }
    else {
        ofSetColor(material.albedo);
    }
    
}

Sphere::Sphere(float radius) {
    setScale(radius);
    primitive.setRadius(radius);
}

boost::optional<Collision> Sphere::intersect(const Ray& ray) {
    float base = ray.direction.dot(ray.position);
    float discr = base * base - ray.position.dot(ray.position) + 1;
    if (discr <= 0) return boost::none;
    float root = sqrt(discr);
    float dist =  min(-base-root, -base+root);
    Vector hitpos = ray.at(dist);
//    return Collision(ray, *this, hitpos, Normal(hitpos - getPosition()), dist);
    return Collision(ray, *this, hitpos, Normal(hitpos - getPosition()), dist);
}

void Sphere::draw() {
    Shape::draw();
    primitive.setTransformMatrix(getGlobalTransformMatrix());
    primitive.drawWireframe();
}

Plane::Plane(Normal normal) : normal(normal) {}

float planar_distance(const Ray& ray, const Vector& position, const Normal& normal) {
    float denom = ray.direction.dot(normal);
    if (denom < 1e-5) return -1;
    float num = (position - ray.position).dot(normal);
    float dist = num / denom;
    if (num < 0) return -1;
    return dist;
}

//bool Plane::intersect(const Ray& ray) const {
//    float dist = planar_distance(ray, getPosition(), normal);
//    if (dist >= 0) {
//        Collision(ray, *this, ray.at(dist), normal, dist);
//    }
//    return boost::none;
//}

Disk::Disk(Normal normal, float radius=1.0) : normal(normal) {
    setScale(radius);
}

float Disk::getRadius() const {
    return 1; // todo, use scale
}

boost::optional<Collision> Disk::intersect(const Ray& ray) {
    float dist = planar_distance(ray, getPosition(), normal);
    if (dist >= 0 && dist < getRadius()) {
        return Collision(ray, *this, ray.at(dist), normal, dist);
    }
    return boost::none;
}

//boost::optional<Collision> Box::intersect(const Ray& ray) const {
//    Vector d = ray.direction;
//    Vector p = ray.position;
//    float min_x = (1 - d.x) / p.x;
//    float max_x = (1 + d.x) / p.x;
//    float min_y = (1 - d.y) / p.y;
//    float max_y = (1 + d.y) / p.y;
//    float min_z = (1 - d.z) / p.z;
//    float max_z = (1 + d.z) / p.z;
//    float best = std::numeric_limits<float>::max();
////    if (min_x < 0 & )
////    if (min_x)
////    *hit = Collision(ray, this, ray.position + best * ray.direction, Normal(), best)
//    return best != std::numeric_limits<float>::min();
//}

Triangle::Triangle(Vector a, Vector b, Vector c) : left(b - a), right(c - a), normal(Normal(left.cross(right))) {
    setPosition(a);
}
//
//boost::optional<Collision> Triangle::intersect(const Ray& ray) const {
//    float dist = planar_distance(ray, getPosition(), normal);
//    if (dist >= 0) {
//        Vector point = ray.at(dist);
//        Vector k = point - getPosition();
//        float barycentric_x = left.getNormalized().dot(k);
//        float barycentric_y = right.getNormalized().dot(k);
//        float sum = barycentric_x + barycentric_y;
//        if (barycentric_x >= 0 && barycentric_y >= 0 && sum <= 1) {
//            return Collision(ray, *this, point, normal, dist);
//        }
//        return boost::none;
//    }
//}
//
//boost::optional<Collision> Mesh::intersect(const Ray& ray) const {
//    float best = std::numeric_limits<float>::min();
//    bool result = false;
//    for (int i = 0; i < triangles.size(); i++) {
//        Collision* candidate;
//        if (triangles[i].intersect(ray, candidate) && candidate->distance < best) {
//            best = candidate->distance;
//            hit = candidate;
//            result = true;
//        }
//    }
//    return result;
//}

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


Shape unit_shape = Shape();
