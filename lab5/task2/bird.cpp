#include "bird.h"

Bird::Bird(double y, double speed, double acce)
    : y(y), speed(speed), acce(acce) {}

void Bird::tick() {
    y += speed;
    speed += acce;
}

int Bird::get_y() const { return (int)y; }
void Bird::set_v(double new_speed) { speed = new_speed; }