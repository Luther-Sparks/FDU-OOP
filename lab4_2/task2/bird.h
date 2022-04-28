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

    // draw the bird on the display
    void draw(Display& display) const override;
    // update the bird's porperties according to key input
    void tick(int key) override;
    // check if the specified position is inside the bird
    bool is_inside(int x, int y) const override;
    Type type() const override { return Type::Bird; }
    // detect collision with the specified object
    bool detect_collide(Object& obj) override;
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