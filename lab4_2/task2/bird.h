#ifndef BIRD_GUARD
#define BIRD_GUARD
#include <utility>
#include "../game/object.h"
class Bird : public Object {
public:
    Bird() = default;
    Bird(double x, double y, double vx, double vy, double ax, double ay);
    Bird& operator=(const Bird&) = default;
    ~Bird() = default;

    void draw(Display& display) const override;
    void tick(int dx, int dy);
    bool is_inside(int x, int y) const override;
    Type type() const override { return Type::Bird; }
    bool in_screen(Object& border) override;
    bool if_collide(Object& obj) override;
    std::pair<int, int> get_pos() const;
    std::pair<double, double> get_v() const;
    std::pair<double, double> get_a() const;
    void set_pos(int _x, int _y);
    void set_v(double _vx, double _vy);
    void set_a(double _ax, double _ay);

private:
    double x, y, vx, vy, ax, ay;
};
#endif