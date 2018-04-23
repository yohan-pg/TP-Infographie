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
#include "ofxDatGui.h"

class App : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void render();
    void exit();
    
    GUI gui;
    
    ofFbo viewport;
    ofFbo renderview;
    
    std::thread render_thread;
    
    int view_width;
    int view_height;
    
    double mouseX;
    double mouseY;
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
};

