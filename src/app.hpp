#pragma once

#include "ofMain.h"
#include "scene.hpp"
#include "camera.hpp"
#include "transform.hpp"
#include "vector.hpp"
#include "material.hpp"
#include "shape.hpp"
#include "light.hpp"
#include "vector.hpp"
#include "gui.hpp"
#include <thread>
#include <math.h>
#include "ofxDatGui.h"
#include "triangulation.hpp"

class App : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void render();
    void exit();
    
    ofxDatGuiScrollView* sview;
    ofPlanePrimitive grid;
    
    ofFbo viewport;
    ofFbo gridline_buffer;
    ofFbo renderview;
    
    const int thread_count = 1;
    vector<std::thread> threads;
    
    int view_width;
    int view_height;
    
    float mouseX;
    float mouseY;
    float pressX;
    float pressY;
    bool dragging;
        
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseScrolled(int x, int y, float scrollX, float scrollY);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void mouseEvent(ofMouseEventArgs args);
    
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
    
    // fonction d'Žvaluation d'une courbe de BŽzier cubique (4 points de contr™le)
    inline void bezier_cubic(
                             float t,
                             float p1x, float p1y, float p1z,
                             float p2x, float p2y, float p2z,
                             float p3x, float p3y, float p3z,
                             float p4x, float p4y, float p4z,
                             float&  x, float& y, float&  z)
    {
        float u = 1 - t;
        float uu = u * u;
        float uuu = uu * u;
        float tt = t * t;
        float ttt = tt * t;
        
        x = uuu * p1x + 3 * uu * t * p2x + 3 * u * tt * p3x + ttt * p4x;
        y = uuu * p1y + 3 * uu * t * p2y + 3 * u * tt * p3y + ttt * p4y;
        z = uuu * p1z + 3 * uu * t * p2z + 3 * u * tt * p3z + ttt * p4z;
    }
};

