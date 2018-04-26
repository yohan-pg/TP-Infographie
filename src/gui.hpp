//
//  gui.hpp
//  GigaRay
//
//  Created by Yohan Poirier-Ginter on 2018-04-23.
//
//

#ifndef gui_hpp
#define gui_hpp

#include <stdio.h>
#include "ofxDatGui.h"

#include "light.hpp"
#include "scene.hpp"
#include "shape.hpp"

class GUI {
public:
    
    float width;
    
    ofxDatGui* leftPane;
    ofxDatGui* rightPane;
    
    ofxDatGuiFolder* fichier;
    ofxDatGuiFolder* scene_folder;
    ofxDatGuiFolder* camera;
    ofxDatGuiFolder* materiaux;
    ofxDatGuiFolder* mesh;
    ofxDatGuiFolder* light;
    ofxDatGuiFolder* creation;
    ofxDatGuiScrollView* layerView;
    
    void openModel();
    void openImage(string path);
    void saveImage(string path);
    
    void setup(float width);
    void draw();
    
    void update();
    
    void onButtonEvent(ofxDatGuiButtonEvent e);
    void onSliderEvent(ofxDatGuiSliderEvent e);
    void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
    void onScrollViewEvent(ofxDatGuiScrollViewEvent e);
    void onDropdownEvent(ofxDatGuiDropdownEvent e);
    
    void refreshList();
    
};

extern GUI gui;


#endif /* gui_hpp */

