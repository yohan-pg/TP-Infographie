//
//  film.cpp
//  TP2
//
//  Created by Yohan Poirier-Ginter on 2018-04-15.
//
//

#include "film.hpp"
#include "scene.hpp"

mutex filmlock;


void Film::allocate(int _width, int _height) {
    width = _width;
    height = _height;
    aspect = width / height;
    buffer.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
    buffer.setColor(Color(0,0,0,0));
    for (int i = 0; i <= width; i++) {
        vector<int> count_row;
        vector<Color> value_row;
        for (int j = 0; j <= height; j++) {
            count_row.push_back(0);
            value_row.push_back(Color(0,0,0,1));
        }
        counts.push_back(count_row);
        values.push_back(value_row);
    }

}

void Film::set(int i, int j, Color color) {
    filmlock.lock();
    filmlock.unlock();
    Color currentColor = values[i][j];
    Color newColor = currentColor + (color - currentColor) /  (++counts[i][j]);
    newColor.a = 1;
    values[i][j] = newColor;
    buffer.setColor(i, j, newColor);
    
    
}

void Film::draw(int x, int y) {
    buffer.draw(x, y);
}

void Film::clear() {
    filmlock.lock();
    buffer.setColor(Color(0,0,0,0));
    for (int i = 0; i <= width; i++) {
        for (int j = 0; j <= height; j++) {
            counts[i][j] = 0;
            values[i][j] = Color(0,0,0,0);
        }
    }
    filmlock.unlock();
}

void Film::update() {
    buffer.update();
}
