#include "gui.hpp"

GUI gui;

void GUI::setup(float w) {
    
    width = w;
    
    // Left Pane
    
    leftPane = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
    
    leftPane->setWidth(width + 1);
    
        fichier = leftPane->addFolder("Fichier", ofColor::grey);
        fichier->addButton("Ouvrir un modele");
        fichier->addButton("Enregister en image");
    
    leftPane->addBreak();
    
        scenefolder = leftPane->addFolder("Scene", ofColor::darkCyan);
        scenefolder->addColorPicker("Background", ofColor::white);
        scenefolder->addColorPicker("Ambient", ofColor::white);
    
    leftPane->addBreak();
    
        creation = leftPane->addFolder("Creation", ofColor::yellow);
        creation->addButton("Add Point");
        creation->addButton("Add Spot");
        creation->addButton("Add Ambient");
        creation->addBreak();
    
    leftPane->addBreak();
    
        camera = leftPane->addFolder("Camera", ofColor::greenYellow);
        camera->addSlider("FOV", 0.0, 10.0, 0.0);
        camera->addSlider("DOF", 0.0, 10.0, 0.0);
        camera->addToggle("Orthographic", false);
    
    leftPane->addBreak();
    
        materiaux = leftPane->addFolder("Materiel", ofColor::orangeRed);
        materiaux->addSlider("Metalness", 0.0, 0.0, 1.0);
        materiaux->addSlider("Roughness", 0.0, 10.0, 0.0);
        materiaux->addBreak();
        materiaux->addSlider("Transmission", 0.0, 10.0, 0.0);
        materiaux->addSlider("IOR", 0.0, 10.0, 0.0);
        materiaux->addBreak();
        materiaux->addSlider("Specular", 0.0, 10.0, 0.0);
        materiaux->addColorPicker("Specular Color", ofColor::white);
        materiaux->addBreak();
        materiaux->addColorPicker("Albedo", ofColor::white);
        materiaux->addBreak();
    
    leftPane->addBreak();
    
        mesh = leftPane->addFolder("Mesh", ofColor::white);
        mesh->addToggle("Smooth", true);
        mesh->addSlider("Subdivs", 0, 3, 0);
        mesh->addBreak();
    
    leftPane->addBreak();
    
        light = leftPane->addFolder("Light", ofColor::yellow);
        light->addColorPicker("Color");
        light->addSlider("Intensity", 0, 10, 1);
        light->addBreak();
    
    leftPane->addBreak()->setHeight(3000.0);
    
    leftPane->onButtonEvent(this, &GUI::onButtonEvent);
    leftPane->onSliderEvent(this, &GUI::onSliderEvent);
    leftPane->onColorPickerEvent(this, &GUI::onColorPickerEvent);
    
    // Right Pane
    
    rightPane = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
    rightPane->setWidth(width+20);
    
    rightPane->addLabel("Courbes");
    
    rightPane->addBreak()->setHeight(218.0);
    
    rightPane->addLabel("Elements");
    
    rightPane->addBreak()->setHeight(3000.0);
    
    layerView = new ofxDatGuiScrollView("ok", 24);
    layerView->setWidth(width+20);
    layerView->setPosition(width, 500);

}

void GUI::update() {
    if (dynamic_cast<Light*>(scene.selection)) {
        light->setOpacity(1.0);
        light->setEnabled(true);
    } else {
        light->setOpacity(0.5);
        light->setEnabled(false);
    }
    
//    if (dynamic_cast<Shape*>(scene.selection)) {
//        materiaux->setOpacity(1.0);
//        materiaux->setEnabled(true);
//    } else {
//        materiaux->setOpacity(0.5);
//        materiaux->setEnabled(false);
//    }
//
//    if (dynamic_cast<Mesh *>(scene.selection)) {
//        mesh->setOpacity(1.0);
//        mesh->setEnabled(true);
//    } else {
//        mesh->setOpacity(0.5);
//        mesh->setEnabled(false);
//    }
    
    scene.background = leftPane->getColorPicker("Background")->getColor();
    scene.ambient = leftPane->getColorPicker("Ambient")->getColor();
    
    scene.camera.setOrtho(leftPane->getToggle("Orthographic")->getChecked());
    scene.camera.setFov(leftPane->getSlider("FOV")->getValue());
    scene.camera.setDof(leftPane->getSlider("DOF")->getValue());
    
    layerView->clear();
    for (int i = 0; i < scene.elements.size(); i++) {
        layerView->add("  " + scene.elements[i]->getName());
    }

}

void GUI::draw() {
    
}

void GUI::onButtonEvent(ofxDatGuiButtonEvent e){
    if (e.target->is("Ouvrir un modele")) {
        // assimp load mesh
    }
    
    else if (e.target->is("Enregister en image")) {
        ofFileDialogResult openFileResult = ofSystemSaveDialog("mon-image.jpg", "Sauvegarde");
        if (openFileResult.bSuccess) {
            saveImage(openFileResult.getPath());
        }
        else {
            ofLogVerbose("Cancel");
        }
    }
    
    else if (e.target->is("Add Point")){
        scene.add(new PointLight());
    }
    
    else if (e.target->is("Add Spot")) {
        scene.add(new SpotLight());
    }
    
    else if (e.target->is("Add Ambient")) {
        scene.add(new AmbientLight());
    }
    
}

void GUI::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    scene.film.clear();
    switch (e.child) {
        case 0: break;
    }
}

void GUI::onSliderEvent(ofxDatGuiSliderEvent e) {
    scene.film.clear();
}

void GUI::onColorPickerEvent(ofxDatGuiColorPickerEvent e) {
    scene.film.clear();
    if (e.target->is("Fond")) {
        float H;
        float S;
        float B;
        e.color.getHsb(H,S,B);
        leftPane->getSlider("H")->setValue(H/255);
        leftPane->getSlider("S")->setValue(S/255);
        leftPane->getSlider("B")->setValue(B/255);
    }
    else if (e.target->is("Trait")) {
        float H;
        float S;
        float B;
        e.color.getHsb(H,S,B);
        leftPane->getSlider("H ")->setValue(H/255);
        leftPane->getSlider("S ")->setValue(S/255);
        leftPane->getSlider("B ")->setValue(B/255);
    } else if (e.target->is("Background")) {
    }
}

void GUI::saveImage(string path) {
    ofImage image;
    image.grabScreen(width, 0, ofGetWidth()-width-10, ofGetHeight());
    image.save(path);
}


