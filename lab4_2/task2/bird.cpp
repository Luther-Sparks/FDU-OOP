#include "bird.h"

#include <cmath>

const double g = 0.1;
const double v_tap_up = -1;
const double v_tap_left = -1;
const double a_tap_left = 0.1;
const double v_tap_right = 1;
const double a_tap_right = -0.1;

Bird::Bird(double x, double y, double vx, double vy, double ax, double ay)
    : x(x), y(y), vx(vx), vy(vy), ax(ax), ay(ay) {}

std::pair<int, int> Bird::get_pos() const {
    return std::make_pair((int)std::round(x), (int)std::round(y));
}
std::pair<double, double> Bird::get_v() const { return std::make_pair(vx, vy); }
std::pair<double, double> Bird::get_a() const { return std::make_pair(ax, ay); }
void Bird::set_pos(int _x, int _y) {
    x = _x;
    y = _y;
}

void Bird::set_v(double _vx, double _vy) {
    vx = _vx;
    vy = _vy;
}

void Bird::set_a(double _ax, double _ay) {
    ax = _ax;
    ay = _ay;
}

void Bird::draw(Display& display) const {
    // TODO: draw the bird on the display
    // hint: you should check if the bird is inside the display
    /* Your code here */
}

bool Bird::is_inside(int x, int y) const {
    // TODO: check if position (x, y) is inside bird
    /* Your code here */
}

void Bird::tick(int key) {
    // TODO: update the bird's properties according to key input
    /* Your code here */
}

bool Bird::detect_collide(Object& obj) {
    // TODO: detect collision with the specified object
    /* Your code here */
}