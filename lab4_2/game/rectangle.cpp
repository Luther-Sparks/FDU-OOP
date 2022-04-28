#include "rectangle.h"

void Rectangle::draw(Display& display) const {
    display.put_horizontal_line(x, y, width, '-');
    display.put_horizontal_line(x, y + height - 1, width, '-');
    display.put_vertical_line(x, y, height, '|');
    display.put_vertical_line(x + width - 1, y, height, '|');
}

void Rectangle::tick([[maybe_unused]] int key) { return; }

bool Rectangle::is_inside(int x, int y) const {
    if (x >= this->x && x <= this->x + width && y >= this->y &&
        y <= this->y + height) {
        return true;
    }
    return false;
}

bool Rectangle::detect_collide(Object& obj) {
    // Iterate through all the points of the object
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (obj.is_inside(this->x + i, this->y + j)) {
                valid = false;
                return true;
            }
        }
    }
    return false;
}