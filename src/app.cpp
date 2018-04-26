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

boost::optional<Collision> test() {
    return boost::none;
    return Collision(unit_ray, unit_shape, Vector(), Normal(), 1);
}


void App::setup() {
    scene.camera.reset();
    ofSetVerticalSync(true);
    
    int width = ofGetWindowWidth();
    int height = ofGetWindowHeight();

    
    view_width = width - gui.width * 2;
    view_height = height / 2;
    
    viewport.allocate(view_width, view_height, GL_RGBA, 8);
    renderview.allocate(view_width, view_height, GL_RGBA, 8);
    scene.film.allocate(view_width, view_height);
    
    for (int i = 0; i < thread_count; i++) {
        threads.push_back(thread(&App::render, this));
    }
    
    Collision* c;
    
    auto *l = new PointLight();
    l->setPosition(Vector(0,4,2));
    scene.add(l);

    auto *p = new Sphere(1);
    p->setPosition(Vector(0,0,0));
    scene.add(p);
    
//    auto *p2 = new Sphere(0.5);
//    p2->setPosition(Vector(0,,0));
//    scene.add(p2);

    
    gui.setup(width * 0.16);
}


void App::render() {
    while (!exited) {
        scene.camera.render(scene.film);
    }
}

void App::update() {
    scene.film.update();
    gui.update();
}

void App::draw() {
    ofClear(125);
    ofEnableAlphaBlending();
    
    scene.film.draw(0, 0);
    renderview.begin();
        ofSetColor(scene.background);
        ofDrawRectangle(0, 0, scene.film.width, scene.film.height);
        ofSetColor(255);
        scene.film.draw(0, 0);
    renderview.end();
    renderview.draw(gui.width, 0);

    ofEnableDepthTest();
    viewport.begin();
        ofClear(125);
        scene.camera.begin();
            ofSetColor(255);
//            for(int i = 0; i < scene.shapes.size(); i++) {
//                scene.shapes[i]->draw();
//            }
            scene.draw();
        scene.camera.end();
    viewport.end();
    viewport.draw(gui.width, view_height);
    ofDisableDepthTest();
    
    gui.draw();
}

void App::keyPressed(int key) {

}

void App::keyReleased(int key) {
    
    float d = ofGetKeyPressed(OF_KEY_ALT) ? 0.1 : 1;
    switch (key) {
        case 'u':
        case 'o':
            scene.camera.toggleOrtho();
            break;
        case 'r':
            scene.camera.reset();
            
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

void App::mousePressed(int x, int y, int button) {
    pressX = x;
    pressY = y;
    if (x > gui.width && x < ofGetWidth() - gui.width - 10) {
        dragging = true;
    }
}

void App::mouseReleased(int x, int y, int button) {
    scene.film.clear();
    if (x > gui.width &&
        x < ofGetWidth() - gui.width &&
        Vector(pressX, pressY, 0).distance(Vector(x, y, 0)) < 3) {
        scene.select(x-gui.width, y-scene.film.height);
    }
    dragging = false;
}

void App::mouseEntered(int x, int y) {

}

void App::mouseExited(int x, int y) {

}

void App::mouseScrolled(int x, int y, float scrollX, float scrollY) {
    scene.film.clear();
    scene.camera.move(0.f, 0.f, scrollY);
}

void App::windowResized(int w, int h) {
    
}

void App::gotMessage(ofMessage msg) {
    
}

void App::dragEvent(ofDragInfo dragInfo) {
    
}

void App::exit() {
    exited = true;
    for (int i = 0; i < threads.size(); i++) {
        threads[i].join();
    }
}
