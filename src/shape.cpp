//
//  shape.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "shape.hpp"





//
//
//Collision::Collision(const Ray& ray, const Shape& shape, Vector position, Vector normal, float distance)
//: ray(ray), shape(shape), position(position), normal(normal), distance(distance) {
//    hit = true;
//}
//
//
//bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1)
//{
//    float discr = b * b - 4 * a * c;
//    if (discr < 0) return false;
//    else if (discr == 0) {
//        x0 = x1 = - 0.5 * b / a;
//    }
//    else {
//        float q = (b > 0) ?
//        -0.5 * (b + sqrt(discr)) :
//        -0.5 * (b - sqrt(discr));
//        x0 = q / a;
//        x1 = c / q;
//    }
//    return true;
//}
//
//Collision Sphere::intersect(const Ray& ray) const {
//    
//}
//
//Collision Plane::intersect(const Ray& ray) const {
//    float num = (getPosition() - ray.position).dot(normal);
//    float denum = ray.direction.dot(normal);
//    float dist = num / denum;
//    if (dist < 0) return Missed;
//    return Collision(ray, *this, ray.position + dist * ray.direction, normal, dist);
//}
//
//Collision Disk::intersect(const Ray& ray) const {
//    float num = (getPosition() - ray.position).dot(normal);
//    float denum = ray.direction.dot(normal);
//    float dist = num / denum;
//    Vector hit = ray.position + dist * ray.direction;
//    if (dist < 0) return Missed;
//    if ((hit - getPosition()).length() > radius) return Missed;
//    return Collision(ray, *this, hit, normal, dist);
//}
//
//Collision Box::intersect(const Ray& ray) const {
//    
//}
//
//Collision Triangle::intersect(const Ray& ray) const {
//    float num = (getPosition() - ray.position).dot(normal);
//    float denum = ray.direction.dot(normal);
//    float dist = num / denum;
//    
//}
//
//Collision Mesh::intersect(const Ray& ray) const {
//    float bestDist = std::numeric_limits<float>::min();;
//    Collision best = Missed;
//    for (int i = 0; i < triangles.size(); i++) {
//        auto coll = triangles[i].intersect(ray);
//        if (coll.distance < bestDist) {
////            best = coll;
//            bestDist = coll.distance;
//        }
//    }
//    return best;
//}


string Shape::getName() {
    return "Shape";
}

string Plane::getName() {
    return "Plane";
}

string Disk::getName() {
    return "Disk";
}

string Box::getName() {
    return "Box";
}

string Sphere::getName() {
    return "Sphere";
}

string Triangle::getName() {
    return "Triangle";
}

string Mesh::getName() {
    return "Mesh";
}
