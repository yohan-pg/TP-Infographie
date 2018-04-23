//
//  film.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "film.hpp"

void Film::allocate(int _width, int _height) {
    width = _width;
    height = _height;
    aspect = width/height;
    buffer.allocate(width, height, OF_IMAGE_COLOR);
    counts.allocate(width, height, OF_IMAGE_COLOR);
}


//void Fil

void Film::set(int i, int j, Color color) {
    /* Garde une 'running average' de la couleur des pixels */
    buffer.setColor(i, j, color);
}

void Film::draw(int x, int y) {
    buffer.draw(x, y);
}

void Film::clear() {
    buffer.clear();
    counts.clear();
}
