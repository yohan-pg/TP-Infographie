//
//  sampler.cpp
//  GigaRay
//
//  Created by Yohan Poirier-Ginter on 2018-04-23.
//
//

#include "sampler.hpp"
#include "vector.hpp"

using namespace Sampler;
using namespace std;

default_random_engine generator;
uniform_real_distribution<float> distribution(0, 1);

auto randf = bind(distribution, generator);

float Sampler::uniform_float() {
    return randf();
}

float Sampler::uniform_int(int inf, int sup) {
    return floor(ofLerp(inf, sup, randf()));
}

Vector Sampler::uniform_vector() {
    return Vector(randf(), randf(), randf());
}

float Sampler::uniform_angle() {
    return randf() * 360;
}

//Vector Sampler::hemisphere_vector() {
//    float a = randf();
//    float sin_theta = sqrtf(1 - a * a);
//    float phi = 2 * 3.1416 * randf();
//    float x = sin_theta * cosf(phi);
//    float z = sin_theta * sinf(phi);
//    return Vector(x, a, z);
//}

Vector Sampler::sphere_vector() {
    Vector dir;
    do {
        dir = Vector(2*randf()-1, 2*randf()-1, 2*randf()-1);
    } while (dir.length() > 1);
    return dir;
}

Vector Sampler::hemisphere_vector(Normal normal) {
    Vector dir;
    do {
       dir = Vector(2*randf()-1, 2*randf()-1, 2*randf()-1);
    } while (dir.length() > 1 && normal.dot(dir));
    return dir;
}

Vector Sampler::uniform_circle() {
    while (true) {
        float a = randf();
        float b = randf();
        if (a*a + b*b <= 1) {
            return Vector(a, b, 0);
        }
    }
}
