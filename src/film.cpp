//
//  film.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "film.hpp"
#include "scene.hpp"

void Film::allocate(int _width, int _height) {
    width = _width;
    height = _height;
    aspect = width / height;
    buffer.allocate(width, height, OF_IMAGE_COLOR);
    buffer.setColor(scene->background);
    for (int i = 0; i <= width; i++) {
        vector<int> row;
        for (int j = 0; j <= height; j++) {
            row.push_back(0);
        }
        counts.push_back(row);
    }
}

void Film::set(int i, int j, Color color) {
    Color currentColor = buffer.getColor(i, j);
    Color newColor = currentColor + (color - currentColor) / (++counts[i][j] + 1);
    buffer.setColor(i, j, newColor);
}

void Film::draw(int x, int y) {
    buffer.draw(x, y);
}

void Film::clear() {
    buffer.setColor(scene->background);
    for (int i = 0; i <= width; i++) {
        for (int j = 0; j <= height; j++) {
            counts[i][j] = 0;
        }
    }
}

void Film::update() {
    buffer.update();
}
