//
//  curve.cpp
//  GigaRay
//
//  Created by Yohan Poirier-Ginter on 2018-04-29.
//
//

#include "curve.hpp"

void Curve::setup() {
    line_resolution = 100;
    for (index = 0; index <= line_resolution; ++index)
        line_renderer.addVertex(ofPoint());
    
    framebuffer_width = ofGetWidth();
    framebuffer_height = ofGetHeight();
    
    initial_position1 = { 1060, 240, 0 };
    initial_position2 = { 1130.95, 171.03, 0. };
    initial_position3 = { 1201.9, 102.06, 0. };
    initial_position4 = { 1275, 31, 0 };
    
    ctrl_point1 = initial_position1;
    ctrl_point2 = initial_position2;
    ctrl_point3 = initial_position3;
    ctrl_point4 = initial_position4;
}

void Curve::update() {
    for (index = 0; index <= line_resolution; ++index)
    {
        bezier_cubic(index / (float)line_resolution,
                     ctrl_point1.x, ctrl_point1.y, ctrl_point1.z,
                     ctrl_point2.x, ctrl_point2.y, ctrl_point2.z,
                     ctrl_point3.x, ctrl_point3.y, ctrl_point3.z,
                     ctrl_point4.x, ctrl_point4.y, ctrl_point4.z,
                     position.x, position.y, position.z);
        // affecter la position du point sur la courbe
        line_renderer[index] = position;
    }
}

float Curve::at(int i) {
    float x, y, z;
    bezier_cubic(i / (float)255,
                         ctrl_point1.x, ctrl_point1.y, ctrl_point1.z,
                         ctrl_point2.x, ctrl_point2.y, ctrl_point2.z,
                         ctrl_point3.x, ctrl_point3.y, ctrl_point3.z,
                         ctrl_point4.x, ctrl_point4.y, ctrl_point4.z,
                  x, y, z);
    return 1 - (y - ctrl_point4.y) / ctrl_point1.y*0.9;
}

void Curve::draw() {
    ofEnableSmoothing();
    ofSetColor(125, 125, 125);
    line_renderer.draw();
    ofSetColor(255, 255, 255);
    ofDrawEllipse(ctrl_point1.x, ctrl_point1.y, 7, 7);
    ofDrawEllipse(ctrl_point2.x, ctrl_point2.y, 7, 7);
    ofDrawEllipse(ctrl_point3.x, ctrl_point3.y, 7, 7);
    ofDrawEllipse(ctrl_point4.x, ctrl_point4.y, 7, 7);
}

void Curve::mousePressed(int x, int y) {
    if (x <= ctrl_point2.x + 10 && x >= ctrl_point2.x - 10
        && y <= ctrl_point2.y + 10 && y >= ctrl_point2.y - 10)
    {
        selected_ctrl_point = &ctrl_point2;
        ptsSelected = true;
    }
    
    if (x <= ctrl_point3.x + 10 && x >= ctrl_point3.x - 10
        && y <= ctrl_point3.y + 10 && y >= ctrl_point3.y - 10)
    {
        selected_ctrl_point = &ctrl_point3;
        ptsSelected = true;
    }
}

void Curve::mouseReleased(int x, int y) {
    ptsSelected = false;
}

void Curve::mouseDragged(int x, int y) {
    if (ptsSelected == true
        && x > ofGetWidth() - 220
        && x < ofGetWidth()
        && y > 30
        && y < 240)
    {
        selected_ctrl_point->x = x;
        selected_ctrl_point->y = y;
    }
}

inline void Curve::bezier_cubic(float t,
                         float p1x, float p1y, float p1z,
                         float p2x, float p2y, float p2z,
                         float p3x, float p3y, float p3z,
                         float p4x, float p4y, float p4z,
                         float&  x, float& y, float&  z) {
    float u = 1 - t;
    float uu = u * u;
    float uuu = uu * u;
    float tt = t * t;
    float ttt = tt * t;
    
    x = uuu * p1x + 3 * uu * t * p2x + 3 * u * tt * p3x + ttt * p4x;
    y = uuu * p1y + 3 * uu * t * p2y + 3 * u * tt * p3y + ttt * p4y;
    z = uuu * p1z + 3 * uu * t * p2z + 3 * u * tt * p3z + ttt * p4z;
}
