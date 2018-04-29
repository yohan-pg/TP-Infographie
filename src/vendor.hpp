
#pragma once

#ifndef vendor_hpp
#define vendor_hpp

#include <stdio.h>
#include "ofMain.h"
#include "vector.hpp"
#include "transform.hpp"

Vector refract(const Vector &ingoing, Normal normal, float ior);
float fresnel(const Vector &ingoing, Normal normal, float ior);

#endif /* material_hpp */
