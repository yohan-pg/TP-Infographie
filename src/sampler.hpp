//
//  sampler.hpp
//  GigaRay
//
//  Created by Yohan Poirier-Ginter on 2018-04-23.
//
//

#ifndef sampler_hpp
#define sampler_hpp

#include <stdio.h>
#include <math.h>
#include <random>
#include "vector.hpp"


namespace Sampler {
    float uniform_float();
    float uniform_int(int inf, int sup);
    float uniform_angle();
    float cosine_float();
    float normal_float();
    Vector uniform_vector();
    Vector uniform_circle();
    Vector uniform_sphere();
    Vector uniform_vector();
    Vector hemisphere_vector();
};



#endif /* sampler_hpp */
