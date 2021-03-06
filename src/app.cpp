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

void App::setup() {
    scene.camera.reset();
    ofSetVerticalSync(true);
    
    int width = ofGetWindowWidth();
    int height = ofGetWindowHeight();
    int gui_width = width * 0.16;
    
    view_width = width - gui_width * 2;
    view_height = height / 2;
    
    viewport.allocate(view_width, view_height, GL_RGBA, 8);
    renderview.allocate(view_width, view_height, GL_RGBA, 8);
    gridline_buffer.allocate(view_width, view_height, GL_RGBA, 8);
    scene.film.allocate(view_width, view_height);
    
    for (int i = 0; i < thread_count; i++) {
        threads.push_back(thread(&App::render, this));
    }
    
    auto *l = new SpotLight();
    l->setPosition(Vector(0,1,2));
    scene.add(l);
    
    auto *p = new Sphere();
    scene.add(p);
    
    gui.setup(width * 0.16);
    curve.setup();
    
    sineWave.setup(SINEMIN,SINEMAX,.1);
    sineCam.setAutoDistance(false);
    sineCam.setDistance(12);
    sineCam.setNearClip(0.01);
    sineCam.setTarget(ofVec3f::zero());
    sineCam.lookAt(ofVec3f::zero());
    
    brightnessShader.load("brightness");
    lut.allocate(256, 1, OF_IMAGE_COLOR);
    scene.film.clear();
    
}

void load_demo_1() {
    
}

void App::render() {
    while (!exited) {
        scene.camera.render(scene.film);
    }
}

void App::update() {
    scene.film.update();
    gui.update();
    curve.update();
    lut.update();
    
    for (int i = 0; i < 256; i++) {
        lut.setColor(i, 0, curve.at(i)*256);
    }
    
    static int ID = 0;
    for (int i = 0; i < children.size(); i++) {
        children[i]->reload();
    }
    sineWave.reload();
    shared_ptr<SineWaveChild> child(new SineWaveChild);
    child->setup(SINEMIN, SINEMAX, .1);
    child->set(ID, sineWave.amplitude,sineWave.orangeStart);
    ofAddListener(child->endE, this, &App::childDied);
    children.push_back(child);
    ID++;
}

void App::draw() {
    ofClear(125);
    ofEnableAlphaBlending();
    
    renderview.begin();
        ofSetColor(255,255,255);
        ofDrawRectangle(0, 0, scene.film.width, scene.film.height);
        ofSetColor(255, 255, 255);
        brightnessShader.begin();
            brightnessShader.setUniformTexture("image", scene.film.buffer.getTexture(), 1);
            brightnessShader.setUniformTexture("lut", lut.getTexture(), 2);
            scene.film.draw(0, 0);
        brightnessShader.end();
        if (triangulation.isTriang)
            triangulation.draw();
        if (scene.draw_surface) {
            sineCam.begin();
            sineWave.draw(true);
            for (int i = 0; i < children.size(); i++) {
                children[i]->draw(true);
            }
            sineCam.end();
        }
        renderview.end();
    renderview.draw(gui.width, 0);

    gridline_buffer.begin();
        ofClear(125);
        scene.camera.begin();
            ofSetColor(255, 255, 255);
            ofEnableDepthTest();
            ofPushMatrix();
            if (scene.camera.getOrtho()) {
                ofScale(50, 50, 50);
            }
            ofDrawGrid(1, 100, false, true, true, true);
            ofPopMatrix();
            ofDisableDepthTest();
        scene.camera.end();
    gridline_buffer.end();
    
    viewport.begin();
        ofClear(125);
        ofSetColor(scene.background);
        gridline_buffer.draw(0, 0);
        scene.camera.begin();
            ofEnableDepthTest();
            ofSetColor(255);
            ofPushMatrix();
            if (scene.camera.getOrtho()) {
                ofScale(50, 50, 50);
            }
            scene.draw();
            ofPopMatrix();
            ofSetColor(255);
            ofDisableDepthTest();
        scene.camera.end();
    viewport.end();
    viewport.draw(gui.width, view_height);
    gui.draw();
    curve.draw();
    
    
}

void App::keyPressed(int key) {}

void App::keyReleased(int key) {
    float d = ofGetKeyPressed(OF_KEY_ALT) ? 0.1 : 1;
    switch (key) {
        case 'u':
        case 'o':
            scene.camera.toggleOrtho();
            break;
        case 'r':
            scene.camera.reset();
            scene.film.clear();
            if (triangulation.isTriang)
                triangulation.reset();
            break;
        case 127: // delete
            if (scene.selection) {
                //scene.remove(scene.selection);
            }
        case 356: // left arrow
            if (scene.selection != NULL) {
                scene.selection->move(Vector(-d, 0, 0));
                scene.film.clear();
            }
            break;
        case 358: // right arrow
            if (scene.selection != NULL) {
                scene.selection->move(Vector(d, 0, 0));
                scene.film.clear();
            }
            break;
        case 357: // up arrow
            if (scene.selection != NULL) {
                if (ofGetKeyPressed(OF_KEY_SHIFT)) {
                    scene.selection->move(Vector(0, d, 0));
                } else {
                    scene.selection->move(Vector(0, 0, -d));
                }
                scene.film.clear();
            }
            break;
        case 359: // down arrow
            if (scene.selection != NULL) {
                if (ofGetKeyPressed(OF_KEY_SHIFT)) {
                    scene.selection->move(Vector(0, -d, 0));
                } else {
                    scene.selection->move(Vector(0, 0, d));
                }
                scene.film.clear();
            }
            break;
    }
}

void App::mouseMoved(int x, int y) {
    mouseX = static_cast<float>(x);
    mouseY = static_cast<float>(y);
}

void App::mouseDragged(int x, int y, int button) {
    if (dragging) {
        scene.film.clear();
        float dx = mouseX - x;
        float dy = mouseY - y;
        if ((button == 0) && !ofGetKeyPressed(OF_KEY_SHIFT)) {
            Vector x_movement = dx * scene.camera.move_speed * scene.camera.getXAxis();
            Vector y_movement = -dy * scene.camera.move_speed * scene.camera.getYAxis();
            scene.camera.move(x_movement + y_movement);
            mouseX = static_cast<float>(x);
            mouseY = static_cast<float>(y);
        } else if ((button == 2) || ((button == 0) && ofGetKeyPressed(OF_KEY_SHIFT))) {
            scene.camera.rotateAround(dx < 0 ? max(dx, -5.0f) : min(dx, 5.0f), Vector(0, 0.5, 0), Vector(0, 0, 0));
            scene.camera.lookAt(scene.selection ? scene.selection->getPosition() : Vector(0, 0, 0));
        }
    }
    curve.mouseDragged(x, y);
}

void App::mousePressed(int x, int y, int button) {
    pressX = x;
    pressY = y;
    if (x > gui.width && x < ofGetWidth() - gui.width - 10) {
        dragging = true;
    }
    curve.mousePressed(x, y);
}

void App::mouseReleased(int x, int y, int button) {
    if (x > gui.width &&
        x < ofGetWidth() - gui.width &&
        Vector(pressX, pressY, 0).distance(Vector(x, y, 0)) < 3) {
        scene.select(x-gui.width, y-scene.film.height);
    }
    
    if (dragging) {
        scene.film.clear();
        dragging = false;
    }
    if (triangulation.isTriang)
        triangulation.mouseReleased(x, y, button);
    curve.mouseReleased(x, y);
}

void App::mouseEntered(int x, int y) {

}

void App::mouseExited(int x, int y) {

}

void App::mouseScrolled(int x, int y, float scrollX, float scrollY) {
    scene.film.clear();
    scene.camera.move(scrollY * scene.camera.getZAxis());
}

void App::windowResized(int w, int h) {
    ofSetWindowShape(1280, 720);
}

void App::gotMessage(ofMessage msg) {
    
}

void App::dragEvent(ofDragInfo dragInfo) {
    
}

void App::childDied(int &ID){
    int indexToRemove;
    for (int i = 0; i < children.size(); i++) {
        if (children[i]->ID == ID) {
            indexToRemove = i;
        }
    }
    children.erase(children.begin() + indexToRemove);
}

void App::exit() {
    exited = true;
    for (int i = 0; i < threads.size(); i++) {
        threads[i].join();
    }
}
