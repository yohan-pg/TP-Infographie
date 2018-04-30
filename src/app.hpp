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
#include "curve.hpp"
#include "gui.hpp"
#include <thread>
#include <math.h>
#include "ofxDatGui.h"
#include "triangulation.hpp"
#include "MyEquations.h"

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
  
    Curve curve;
    ofImage lut;
    ofShader brightnessShader;
    
    SineWaveParent sineWave;
    vector<shared_ptr<SineWaveChild>> children;
    void childDied(int &ID);
    ofEasyCam sineCam;
};

