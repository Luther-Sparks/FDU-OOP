#include "rectangle.h"

void Rectangle::draw(Display& display) const {
    display.put_horizontal_line(x, y, width, '-');
    display.put_horizontal_line(x, y + height - 1, width, '-');
    display.put_vertical_line(x, y, height, '|');
    display.put_vertical_line(x + width - 1, y, height, '|');
}

//Add [[maybe_unused]] to suppress warning
void Rectangle::tick([[maybe_unused]] std::map<std::string, std::string>& global_state) {}

bool Rectangle::is_inside(int x, int y) const {
    if (x >= this->x && x <= this->x + width && y >= this->y && y <= this->y + height) {
        return true;
    }
    return false;
}
