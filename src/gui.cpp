#include "gui.hpp"

GUI gui;

void GUI::setup(float w) {
    
    width = w;
    
    // Left Pane
    
    leftPane = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
    
    leftPane->setWidth(width + 1);
    
    leftPane->addButton("Ouvrir Demo 1")->setStripeColor(ofColor::black);
    leftPane->addButton("Ouvrir Demo 2")->setStripeColor(ofColor::black);
    leftPane->addButton("Ouvrir Demo 3")->setStripeColor(ofColor::black);
    
    leftPane->addBreak();
    
        fichier = leftPane->addFolder("Fichier", ofColor::grey);
        fichier->addButton("Ouvrir un modele");
        fichier->addButton("Enregister en image");
    
    leftPane->addBreak();
    
        scene_folder = leftPane->addFolder("scene.", ofColor::darkCyan);
        scene_folder->addColorPicker("Background", scene.background);
        scene_folder->addColorPicker("Ambient", scene.ambient);
    
    leftPane->addBreak();
    
        creation = leftPane->addFolder("Creation", ofColor::yellow);
        creation->addButton("Add Point");
        creation->addButton("Add Spot");
        creation->addButton("Add Ambient");
        creation->addBreak();
    
    leftPane->addBreak();
    
        camera = leftPane->addFolder("Camera", ofColor::greenYellow);
        camera->addSlider("FOV", 30.0, 120.0, scene.camera.getFov());
        camera->addSlider("Aperture Size", 0.0, 4.0, scene.camera.aperture_size);
        camera->addSlider("AA Samples", 1, 64, scene.camera.aa_samples);
        camera->addToggle("Orthographic", scene.camera.getOrtho());
    
    leftPane->addBreak();
    
        materiaux = leftPane->addFolder("Materiel", ofColor::orangeRed);
        materiaux->addSlider("Metalness", 0.0, 0.0, 1.0);
        materiaux->addSlider("Roughness", 0.0, 10.0, 0.0);
        materiaux->addBreak();
        materiaux->addSlider("Transmission", 0.0, 10.0, 0.0);
        materiaux->addSlider("IOR", 0.0, 10.0, 0.0);
        materiaux->addBreak();
        materiaux->addSlider("Specular", 0.0, 10.0, 0.0);
        materiaux->addColorPicker("Specular Tint", ofColor::white);
        materiaux->addBreak();
        materiaux->addColorPicker("Albedo", ofColor::white);
        materiaux->addBreak();
    
    leftPane->addBreak();
    
        mesh = leftPane->addFolder("Mesh", ofColor::white);
        mesh->addToggle("Smooth", true);
//        mesh->addSlider("Subdivs", 0, 3, 0);
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
    
    layerView = new ofxDatGuiScrollView("Layers", 17);
    layerView->setWidth(width+20);
    layerView->setPosition(ofGetWidth()-width-17, 273);
    layerView->onScrollViewEvent(this, &GUI::onScrollViewEvent);
    
    leftPane->setAutoDraw(false);
    rightPane->setAutoDraw(false);
    
    refreshList();
}



void GUI::update() {
    if (auto l = dynamic_cast<Light*>(scene.selection)) {
        light->setOpacity(1.0);
        light->setEnabled(true);
        l->color = leftPane->getColorPicker("Color")->getColor();
        l->intensity = leftPane->getSlider("Intensity")->getValue();
        
    } else {
        light->setOpacity(0.3);
        light->setEnabled(false);
        light->collapse();
        leftPane->update();
    }
    
    if (auto s = dynamic_cast<Shape*>(scene.selection)) {
        
        if (!materiaux->getEnabled()) {
            leftPane->getSlider("Metalness")->setValue(s->material.metalness);
            leftPane->getSlider("Roughness")->setValue(s->material.roughness);
            leftPane->getSlider("Transmission")->setValue(s->material.transmission);
            leftPane->getSlider("IOR")->setValue(s->material.ior);
            leftPane->getSlider("Specular")->setValue(s->material.specular);
            leftPane->getColorPicker("Specular Tint")->setColor(s->material.specularTint);
            leftPane->getColorPicker("Albedo")->setColor(s->material.albedo);
        }
        
        s->material.metalness = leftPane->getSlider("Metalness")->getValue();
        s->material.roughness = leftPane->getSlider("Roughness")->getValue();
        s->material.transmission = leftPane->getSlider("Transmission")->getValue();
        s->material.ior = leftPane->getSlider("IOR")->getValue();
        s->material.specular = leftPane->getSlider("Specular")->getValue();
        s->material.specularTint = leftPane->getColorPicker("Specular Tint")->getColor();
        s->material.albedo = leftPane->getColorPicker("Albedo")->getColor();

        materiaux->setOpacity(1.0);
        materiaux->setEnabled(true);
        
    } else {
        materiaux->setOpacity(0.3);
        materiaux->collapse();
        materiaux->setEnabled(false);
        leftPane->update();
    }

    if (auto m = dynamic_cast<Mesh*>(scene.selection)) {

        if (!mesh->getEnabled()) {
            leftPane->getToggle("Smooth")->setChecked(m->smooth);
        }
        
        m->smooth = leftPane->getToggle("Smooth")->getChecked();
        
        mesh->setOpacity(1.0);
        mesh->setEnabled(true);
    } else {
        mesh->setOpacity(0.3);
        mesh->collapse();
        mesh->setEnabled(false);
        leftPane->update();
    }
    
    scene.background = leftPane->getColorPicker("Background")->getColor();
    scene.ambient = leftPane->getColorPicker("Ambient")->getColor();
    
    scene.camera.setFov(leftPane->getSlider("FOV")->getValue());
    scene.camera.aperture_size = (leftPane->getSlider("Aperture Size")->getValue());
    scene.camera.aa_samples = (leftPane->getSlider("AA Samples")->getValue());
    scene.camera.setOrtho(leftPane->getToggle("Orthographic")->getChecked());
    
    leftPane->update();
    rightPane->update();
    
    for (int i = 0; i < scene.elements.size(); i++) {
        if (scene.selection == scene.elements[i]) {
            layerView->get(i)->setStripe(ofColor(255,255,255), 7);
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
    cout << "WUT" << endl;
    scene.select(scene.elements[e.index]);
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


