//
//  vector.hpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#ifndef vector_hpp
#define vector_hpp

#include <stdio.h>
#include "ofMain.h"

typedef ofVec3f Vector;

class Normal : public Vector {
public:
    Normal();
    Normal(float x, float y, float z);
    Normal(Vector v);
};



#endif /* vector_hpp */
