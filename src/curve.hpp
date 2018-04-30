//
//  curve.hpp
//  GigaRay
//
//  Created by Yohan Poirier-Ginter on 2018-04-29.
//
//

#ifndef curve_hpp
#define curve_hpp

#include <stdio.h>
#include "ofMain.h"

class Curve {
public:
    int line_resolution;
    int index;
    ofPolyline line_renderer;
    float framebuffer_width;
    float framebuffer_height;
    ofVec3f initial_position1;
    ofVec3f initial_position2;
    ofVec3f initial_position3;
    ofVec3f initial_position4;
    ofVec3f ctrl_point1;
    ofVec3f ctrl_point2;
    ofVec3f ctrl_point3;
    ofVec3f ctrl_point4;
    ofVec3f position;
    ofVec3f* selected_ctrl_point;
    bool ptsSelected = false;
    
    void setup();
    void update();
    void draw();
    float at(int i);
    void mousePressed(int x, int y);
    void mouseReleased(int x, int y);
    void mouseDragged(int x, int y);
    
    void bezier_cubic(float t, float p1x, float p1y, float p1z,
                      float p2x, float p2y, float p2z,
                      float p3x, float p3y, float p3z,
                      float p4x, float p4y, float p4z,
                      float&  x, float& y, float&  z);
};


#endif /* curve_hpp */
