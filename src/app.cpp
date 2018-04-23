//
//  app.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-16.
//
//

#include "app.hpp"

using namespace std;

bool exited = false;

void App::setup(){
    scene.camera.reset();
    ofSetVerticalSync(true);
    
    int width = ofGetWindowWidth();
    int height = ofGetWindowHeight();

    gui.setup(width * 0.16);
    view_width = width - gui.width * 2;
    view_height = height / 2;
    
    viewport.allocate(view_width, view_height, GL_RGBA, 8);
    renderview.allocate(view_width, view_height, GL_RGBA, 8);
    scene.film.allocate(view_width, view_height);
    
    render_thread = thread(&App::render, this);
    
}

void App::render() {
    while (!exited) {
//        scene.camera.render(film, scene);
    }
}

void App::update(){
    gui.update();
}

void App::draw(){

    ofEnableDepthTest();
    ofClear(125, 125, 125, 0);

    renderview.begin();
        ofClear(scene.background);
        scene.film.draw(0, 0);
    renderview.end();
    renderview.draw(gui.width, 0);
    
    ofSpherePrimitive sphere;
    
    viewport.begin();
    ofClear(255, 255, 255, 0);
        scene.camera.begin();
            ofSetColor(255, 0, 0);
            sphere.draw();
        scene.camera.end();
    viewport.end();
    viewport.draw(gui.width, view_height);
    
    ofDisableDepthTest();
    
    gui.draw();
    
}

void App::keyPressed(int key){

}

void App::keyReleased(int key){
    switch (key) {
        case 'u':
        case 'o':
            scene.camera.toggleOrtho();
            break;
        case 'r':
            scene.camera.reset();
    }
}

void App::mouseMoved(int x, int y){
    mouseX = static_cast<float>(x);
    mouseY = static_cast<float>(y);
}

void App::mouseDragged(int x, int y, int button){
    if (dragging) {
        float dx = mouseX - x;
        float dy = mouseY - y;
        if ((button == 0) && !ofGetKeyPressed(OF_KEY_SHIFT)) {
            scene.camera.move(dx * scene.camera.move_speed,
                              dy * -scene.camera.move_speed,
                              0.f);
            mouseX = static_cast<float>(x);
            mouseY = static_cast<float>(y);
        } else if ((button == 2) || ((button == 0) && ofGetKeyPressed(OF_KEY_SHIFT))) {
            Vector r = Vector(dx, dy, 0.f).normalize();
            scene.camera.rotateAround(r.length(), Vector(0., 1., 1.), Vector(0.f, 0.f, 0.f));
        }
    }
}

void App::mousePressed(int x, int y, int button){
    if (x > gui.width && x < ofGetWidth() - gui.width - 10) {
        dragging = true;
    }
}

void App::mouseReleased(int x, int y, int button){
    dragging = false;
}

void App::mouseEntered(int x, int y){

}

void App::mouseExited(int x, int y){

}

void App::mouseScrolled(int x, int y, float scrollX, float scrollY) {
    scene.camera.move(0.f, 0.f, scrollY);
}

void App::windowResized(int w, int h){
    
}

void App::gotMessage(ofMessage msg){
    
}

void App::dragEvent(ofDragInfo dragInfo){
    
}

void App::exit() {
    exited = true;
    render_thread.join();
}
