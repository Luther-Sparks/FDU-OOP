#include "bird.h"
#include <cmath>

Bird::Bird(double x, double y, double vx, double vy, double ax, double ay)
    : x(x), y(y), vx(vx), vy(vy), ax(ax), ay(ay) {}

void Bird::tick() {
    x += vx + ax/2;
    y += vy + ay/2;
    vx += ax;
    vy += ay;
}

std::pair<int, int> Bird::get_pos() const { return std::make_pair((int)std::round(x), (int)std::round(y)); }
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
