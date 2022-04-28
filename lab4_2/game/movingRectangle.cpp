#include "movingRectangle.h"

MovingRectangle::MovingRectangle(int x, int y, int width, int height, int dx, int dy) : Rectangle(x, y, width, height), dx(dx), dy(dy) {}

void MovingRectangle::tick([[maybe_unused]]int key) {
    x += dx;
    y += dy;
}