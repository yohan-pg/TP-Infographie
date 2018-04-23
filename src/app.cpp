//
//  app.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-16.
//
//

#include "app.hpp"

void App::setup(){
    //    camera.reset();
    //    ofSetVerticalSync(true);
    //    ofEnableDepthTest();
    //    renderfilm.allocate(400, 400, OF_IMAGE_COLOR);
    
    int width = ofGetWindowWidth();
    int height = ofGetWindowHeight();

    int gui_width = 150;
    int view_width = width - gui_width * 2;
    int view_height = height / 2;
    
    viewport.allocate(800, 800, GL_RGBA, 8);
    renderview.allocate(view_width, view_height, GL_RGBA, 8);
    
}

void App::update(){
}

void App::draw(){
    
    //    renderview.begin();
    //    ofClear(255, 255, 255, 0);
    //    ofSetColor(0,0,0);
    //    ofDrawRectangle(0, 0, view_width, view_height);
    //    camera.begin();
    //    camera.end();
    //    renderview.end();
    //    renderview.draw(gui_width, 0);
    //
    //    ofSpherePrimitive sphere;
    //
    //    viewport.begin();
    //    ofClear(255, 255, 255, 0);
    //    ofSetColor(255, 255, 255);
    //    ofDrawRectangle(0, 0, view_width, view_height);
    //    camera.begin();
    //    ofSetColor(255, 0, 0);
    //    sphere.draw();
    ////    renderfilm.draw(0, 0);
    //    camera.end();
    //    viewport.end();
    //    viewport.draw(gui_width, height / 2);
    
}

void App::keyPressed(int key){

}

void App::keyReleased(int key){
//    switch (key) {
//        case 'u':
//        case 'o':
//            camera.toggleOrtho();
//            break;
//        case 'r':
//            camera.reset();
//    }
}

void App::mouseMoved(int x, int y){
//    mouseX = static_cast<float>(x);
//    mouseY = static_cast<float>(y);
}

void App::mouseDragged(int x, int y, int button){
//    float dx = mouseX - x;
//    float dy = mouseY - y;
//    if ((button == 0) && !ofGetKeyPressed(OF_KEY_SHIFT)) {
//        camera.move(dx * camera.move_speed,
//                    dy * -camera.move_speed,
//                    0.f);
//        mouseX = static_cast<float>(x);
//        mouseY = static_cast<float>(y);
//    } else if ((button == 2) || ((button == 0) && ofGetKeyPressed(OF_KEY_SHIFT))) {
////        Vector r = Vector(dx, dy, 0.f).normalize();
////        cout << r <<Êendl;
////        camera.rotateAround(r.length(), Vector(0., 1., 1.), Vector(0.f, 0.f, 0.f));
//    }
}

void App::mousePressed(int x, int y, int button){

}

void App::mouseReleased(int x, int y, int button){

}

void App::mouseEntered(int x, int y){

}

void App::mouseExited(int x, int y){

}


void App::mouseScrolled(int x, int y, float scrollX, float scrollY) {
    //    camera.move(0.f, 0.f, scrollY);
}

void App::windowResized(int w, int h){
    
}

void App::gotMessage(ofMessage msg){
    
}

void App::dragEvent(ofDragInfo dragInfo){
    
}
