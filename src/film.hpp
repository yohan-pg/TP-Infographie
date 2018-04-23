//
//  film.hpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#ifndef film_hpp
#define film_hpp

#include <stdio.h>
#include "ofMain.h"
#include "color.hpp"

class Film  {
    ofImage buffer;
    ofImage counts;
public:
    float width;
    float height;
    float aspect;
    void allocate(int width, int height);
    void set(int i, int j, Color color);
    void clear();
    void draw(int x, int y);
};


#endif /* film_hpp */
