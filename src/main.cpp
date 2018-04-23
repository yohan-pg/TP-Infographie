#include "ofMain.h"
#include "app.hpp"


int main( ){
	ofSetupOpenGL(800, 600, OF_WINDOW);
	ofRunApp(new App());
}
