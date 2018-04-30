#include "gui.hpp"

GUI gui;

void GUI::setup(float w) {
    
    width = w;
    
    // Left Pane
    
    leftPane = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
    
    leftPane->setWidth(width + 1);
    
    leftPane->addBreak();
    
        fichier = leftPane->addFolder("Fichier", ofColor::grey);
        fichier->addButton("Ouvrir Demo 1")->setStripeColor(ofColor::black);
        fichier->addButton("Ouvrir Demo 2")->setStripeColor(ofColor::black);
        fichier->addButton("Ouvrir Demo 3")->setStripeColor(ofColor::black);
    
    leftPane->addBreak();
    
        scene_folder = leftPane->addFolder("Scene", ofColor::darkCyan);
        scene_folder->addColorPicker("Background", scene.background);
        scene_folder->addColorPicker("Ambient", scene.ambient);
        scene_folder->addSlider("Max Ray Depth", 0.0, 10.0, scene.tracingDepth)->setPrecision(0);
    
    leftPane->addBreak();
    
        creation = leftPane->addFolder("Creation", ofColor::yellow);
        creation->addButton("Add Point");
        creation->addButton("Add Spot");
        creation->addButton("Add Ambient");
        creation->addButton("Add Directional");
        creation->addToggle("Triangulation");
        creation->addToggle("Surface Parametrique");
        creation->addBreak();
    
    leftPane->addBreak();
    
        camera = leftPane->addFolder("Camera", ofColor::greenYellow);
        camera->addSlider("FOV", 30.0, 120.0, scene.camera.getFov());
        camera->addSlider("Aperture Size", 0.0, 4.0, scene.camera.aperture_size)->setPrecision(3);
        camera->addSlider("AA Samples", 1, 64, scene.camera.aa_samples)->setPrecision(0);
        camera->addToggle("Orthographic", scene.camera.getOrtho());
    
    leftPane->addBreak();
    
        materiaux = leftPane->addFolder("Materiel", ofColor::orangeRed);
        materiaux->addColorPicker("Albedo", ofColor::white);
        materiaux->addBreak();
        materiaux->addSlider("Reflection", 0.0, 1.0, 0.0)->setPrecision(3);
        materiaux->addSlider("Refraction", 0.0, 1.0, 0.0)->setPrecision(3);
        materiaux->addSlider("IOR", 0.0, 10.0, 0.0)->setPrecision(1);
        materiaux->addBreak();
        materiaux->addSlider("Specular", 0.0, 1.0, 1.0)->setPrecision(3);
        materiaux->addSlider("Spec Glossiness", 0.0, 30.0, 0.0)->setPrecision(2);
        materiaux->addBreak();
        materiaux->addSlider("Indirect", 0.0, 1.0, 0.0)->setPrecision(3);
        materiaux->addSlider("Indirect Bounces", 1, 12, 0)->setPrecision(0);
        materiaux->addBreak();
    
    leftPane->addBreak();
    
        mesh = leftPane->addFolder("Mesh", ofColor::white);
        mesh->addToggle("Smooth", true);
        mesh->addBreak();
    
    leftPane->addBreak();
    
        light = leftPane->addFolder("Light", ofColor::yellow);
        light->addColorPicker("Color");
        light->addSlider("Intensity", 0, 1, 0.8)->setPrecision(2);
        light->addSlider("Radius", 0, 10, 1)->setPrecision(2);
        light->addSlider("Shadow Samples", 1, 20, 1)->setPrecision(0);
        light->addSlider("Attenuation", 0, 1, 0.1)->setPrecision(3);
        light->addBreak();
    
    leftPane->addBreak()->setHeight(3000.0);
    
    leftPane->onToggleEvent(this, &GUI::onToggleEvent);
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
    
    layerView = new ofxDatGuiScrollView("Layers", 17);
    layerView->setWidth(width+20);
    layerView->setPosition(ofGetWidth()-width-17, 273);
    layerView->onScrollViewEvent(this, &GUI::onScrollViewEvent);
    
    leftPane->setAutoDraw(false);
    rightPane->setAutoDraw(false);
    
    refreshList();
    gui.updateSelection();
}

void GUI::updateSelection() {
    if (auto l = dynamic_cast<Light*>(scene.selection)) {
        light->setOpacity(1.0);
        leftPane->getColorPicker("Color")->setColor(l->color);
        leftPane->getSlider("Intensity")->setValue(l->intensity);
        leftPane->getSlider("Radius")->setValue(l->size);
        leftPane->getSlider("Shadow Samples")->setValue(l->shadowSamples);
        leftPane->getSlider("Attenuation")->setValue(l->attentuation);
    } else {
        light->setOpacity(0.3);
    }
    
    if (auto s = dynamic_cast<Shape*>(scene.selection)) {
        materiaux->setOpacity(1.0);
        leftPane->getColorPicker("Albedo")->setColor(s->material.albedo);
        leftPane->getSlider("Reflection")->setValue(s->material.reflection);
        leftPane->getSlider("Refraction")->setValue(s->material.refraction);
        leftPane->getSlider("IOR")->setValue(s->material.ior);
        leftPane->getSlider("Specular")->setValue(s->material.specularAmount);
        leftPane->getSlider("Spec Glossiness")->setValue(s->material.specularHardness);
        leftPane->getSlider("Indirect")->setValue(s->material.ambient);
        leftPane->getSlider("Indirect Bounces")->setValue(s->material.indirectBounces);
    } else  {
        materiaux->setOpacity(0.3);
    }
    
    if (auto m = dynamic_cast<Mesh*>(scene.selection)) {
        mesh->setOpacity(1.0);
        leftPane->getToggle("Smooth")->setChecked(m->smooth);
        
    } else {
        mesh->setOpacity(0.3);
    }
    
    leftPane->update();
    
    
}

void GUI::update() {
    if (auto l = dynamic_cast<Light*>(scene.selection)) {
        light->setOpacity(1.0);
        l->color = leftPane->getColorPicker("Color")->getColor();
        l->intensity = leftPane->getSlider("Intensity")->getValue();
        l->size = leftPane->getSlider("Radius")->getValue();
        l->shadowSamples = leftPane->getSlider("Shadow Samples")->getValue();
        l->attentuation = leftPane->getSlider("Attenuation")->getValue();
        
    } else if (auto s = dynamic_cast<Shape*>(scene.selection)) {
        s->material.albedo = leftPane->getColorPicker("Albedo")->getColor();
        s->material.reflection = leftPane->getSlider("Reflection")->getValue();
        s->material.refraction = leftPane->getSlider("Refraction")->getValue();
        s->material.ior = leftPane->getSlider("IOR")->getValue();
        s->material.specularAmount = leftPane->getSlider("Specular")->getValue();
        s->material.specularHardness = leftPane->getSlider("Spec Glossiness")->getValue();
        s->material.ambient = leftPane->getSlider("Indirect")->getValue();
        s->material.indirectBounces = leftPane->getSlider("Indirect Bounces")->getValue();
        
    } else if (auto m = dynamic_cast<Mesh*>(scene.selection)) {
        m->smooth = leftPane->getToggle("Smooth")->getChecked();
        mesh->setOpacity(1.0);
    }
    
    scene.background = leftPane->getColorPicker("Background")->getColor();
    scene.ambient = leftPane->getColorPicker("Ambient")->getColor();
    scene.tracingDepth = leftPane->getSlider("Max Ray Depth")->getValue();
    
    scene.camera.setFov(leftPane->getSlider("FOV")->getValue());
    scene.camera.aperture_size = (leftPane->getSlider("Aperture Size")->getValue());
    scene.camera.aa_samples = (leftPane->getSlider("AA Samples")->getValue());
    scene.camera.setOrtho(leftPane->getToggle("Orthographic")->getChecked());
    
    triangulation.setTriang(leftPane->getToggle("Triangulation")->getChecked());
    
    leftPane->update();
    rightPane->update();
    
    for (int i = 0; i < scene.elements.size(); i++) {
        if (scene.selection == scene.elements[i]) {
            layerView->get(i)->setStripe(ofColor(255, 255, 255), 7);
        } else {
            layerView->get(i)->setStripe(ofColor::yellow, 2);
        }
    }
    layerView->update();
}

void GUI::refreshList() {
    layerView->clear();
    for (int i = 0; i < scene.elements.size(); i++) {
        layerView->add("  " + scene.elements[i]->getName());
    }
}

void GUI::draw() {
    leftPane->draw();
    rightPane->draw();
    layerView->draw();
}

void GUI::onButtonEvent(ofxDatGuiButtonEvent e){
    if (e.target->is("Ouvrir un modele")) {
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
        gui.refreshList();
    }
    
    else if (e.target->is("Add Spot")) {
        scene.add(new SpotLight());
        gui.refreshList();
    }
    
    else if (e.target->is("Add Ambient")) {
        scene.add(new AmbientLight());
        gui.refreshList();
    }
    
    else if (e.target->is("Add Directional")) {
        scene.add(new DirectionalLight());
        gui.refreshList();
    }
}

void GUI::onToggleEvent(ofxDatGuiToggleEvent e) {
    if (e.target->is("Triangulation")) {
        leftPane->getColorPicker("Background")->setColor(ofColor(0, 0, 0));
        scene.film.clear();
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

void GUI::onScrollViewEvent(ofxDatGuiScrollViewEvent e) {
    scene.select(scene.elements[e.index]);
}

void GUI::onColorPickerEvent(ofxDatGuiColorPickerEvent e) {
    scene.film.clear();
}

void GUI::saveImage(string path) {
    ofImage image;
    image.grabScreen(width, 0, ofGetWidth()-width-10, ofGetHeight());
    image.save(path);
}


