#include "border.h"

Border::Border(int x, int y, int width, int height)
    : Rectangle(x, y, width, height) {}

bool Border::is_inside(int x, int y) const {
    // On vertical edge
    if (x == this->x || x == this->x + width - 1) {
        if (y >= this->y && y < this->y + height) {
            return true;
        }
    }
    // On horizontal edge
    if (y == this->y || y == this->y + height - 1) {
        if (x >= this->x && x < this->x + width) {
            return true;
        }
    }
    return false;
}

bool Border::detect_collide(Object& obj) {
    // Iterate through all the edges of the object
    // Scan vertically
    for (int i = 0; i < height; i++) {
        if (obj.is_inside(x, y + i)) {
            valid = false;
            return true;
        }
        if (obj.is_inside(x + width - 1, y + i)) {
            valid = false;
            return true;
        }
    }
    // Scan horizontally
    for (int i = 0; i < width; i++) {
        if (obj.is_inside(this->x + i, this->y)) {
            valid = false;
            return true;
        }
        if (obj.is_inside(this->x + i, this->y + height - 1)) {
            valid = false;
            return true;
        }
    }
    return false;
}