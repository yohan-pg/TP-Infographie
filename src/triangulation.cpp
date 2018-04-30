#include "triangulation.hpp"
#include "gui.hpp"

Triangulation triangulation = Triangulation();

//--------------------------------------------------------------
void Triangulation::setup() {
	ofEnableSmoothing();
	ofBackground(0);
}

//--------------------------------------------------------------
void Triangulation::draw() {
	ofNoFill();
	triangulation.draw();
}

//--------------------------------------------------------------
void Triangulation::reset() {
	triangulation.reset();
}

//--------------------------------------------------------------
void Triangulation::mouseReleased(int x, int y, int button) {
	triangulation.addPoint(ofPoint(x - gui.width, y));
	triangulation.triangulate();
}

void Triangulation::toggleTriang() {
	if (getTriang()) {
		disableTriang();
	}
	else {
		enableTriang();
	}
}

bool Triangulation::getTriang() {
	return isTriang;
}

void Triangulation::setTriang(bool setting) {
	if (setting) {
		enableTriang();
	}
	else {
		disableTriang();
	}
}

void Triangulation::enableTriang() {
	isTriang = true;
}

void Triangulation::disableTriang() {
	isTriang = false;
}