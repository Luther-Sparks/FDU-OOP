#include "rectangle.h"

void Rectangle::draw(Display& display) const {
    display.put_horizontal_line(x, y, width, '-');
    display.put_horizontal_line(x, y + height - 1, width, '-');
    display.put_vertical_line(x, y, height, '|');
    display.put_vertical_line(x + width - 1, y, height, '|');
}


void Rectangle::tick(int dx, int dy) {
    x += dx;
    y += dy;
}

bool Rectangle::is_inside(int x, int y) const {
    if (x >= this->x && x <= this->x + width && y >= this->y && y <= this->y + height) {
        return true;
    }
    return false;
}

bool Rectangle::in_screen(Object& border) {
    if (border.is_inside(x, y) && border.is_inside(x + width - 1, y) 
        && border.is_inside(x, y + height - 1) 
        && border.is_inside(x + width - 1, y + height - 1)) {
        return true;
    }
    valid = false;
    return false;
}

bool Rectangle::if_collide(Object& obj) {
    if (obj.is_inside(x, y) || obj.is_inside(x + width - 1, y) 
        || obj.is_inside(x, y + height - 1) 
        || obj.is_inside(x + width - 1, y + height - 1)) {
        valid = false;
        return true;
    }
    return false;
}