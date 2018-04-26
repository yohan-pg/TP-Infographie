#include "ofMain.h"
#include "app.hpp"



int main( ){
	ofSetupOpenGL(1280, 720, OF_WINDOW);
    ofEnableSmoothing();
	ofRunApp(new App());
}
