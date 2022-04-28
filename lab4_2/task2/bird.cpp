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
    auto intx = (int)std::round(x);
    auto inty = (int)std::round(y);
    if (intx > 0 && inty > 0 && intx < display.get_cols() &&
        inty < display.get_rows()) {
        display.put_string(intx, inty, "@");
    }
}

bool Bird::is_inside(int x, int y) const {
    return x == this->x && y == this->y;
}

void Bird::tick(int key) {
    // process key first
    if (key == ' ') {
        set_v(vx, v_tap_up);
        set_a(ax, g);
    } else if (key == 'z') {
        set_v(v_tap_left, vy);
        set_a(a_tap_left, g);
    } else if (key == 'x') {
        set_v(v_tap_right, vy);
        set_a(a_tap_right, g);
    } else {
        if ((vx + ax) * ax >= 0) {
            set_a(0, g);
            set_v(0, vy);
        } else {
            set_a(ax, g);
        }
    }
    // routine actions
    set_v(vx + ax, vy + ay);
    x = x + vx + 1 / 2 * ax;
    y = y + vy + 1 / 2 * ay;
}

bool Bird::detect_collide(Object& obj) {
    if (obj.is_inside(x, y)) {
        valid = false;
        return true;
    }
    return false;
}