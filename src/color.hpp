//
//  color.hpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#ifndef color_hpp
#define color_hpp

#include <stdio.h>
#include "ofMain.h"

typedef ofColor Color;

namespace Colors {
    static const Color BLACK = Color(0, 0, 0);
    static const Color WHITE = Color(255, 255, 255);
    static const Color RED = Color(255, 0, 0);
    static const Color BLUE = Color(0, 0, 255);
    static const Color GREEN = Color(0, 255, 0);
}


#endif /* color_hpp */
