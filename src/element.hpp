//
//  element.hpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#ifndef element_hpp
#define element_hpp

#include <stdio.h>

#include "ofMain.h"
#include "transform.hpp"

class Element : public ofNode {
public:
    virtual string getName();
};

#endif /* element_hpp */
