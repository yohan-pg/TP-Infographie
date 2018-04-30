#pragma once

#include "ofMain.h"
#include "ofxDelaunay.h"

class Triangulation {
public:
	void setup();
	void draw();
	void reset();
	void mouseReleased(int x, int y, int button);

	ofxDelaunay triangulation;
	bool isTriang;
	void toggleTriang();
	bool getTriang();
	void setTriang(bool setting);
	void enableTriang();
	void disableTriang();
};

extern Triangulation triangulation;