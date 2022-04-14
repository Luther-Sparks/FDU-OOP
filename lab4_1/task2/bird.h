#ifndef BIRD_GUARD
#define BIRD_GUARD
#include <utility>
class Bird {
public:
    Bird() = default;
    Bird(double x, double y, double vx, double vy, double ax, double ay);
    Bird& operator=(const Bird&) = default;
    ~Bird() = default;
    
    // every 50ms we will call this function.
    // please think what should we do in this function.
    void tick();
    // get the position <x, y> of bird
    std::pair<int, int> get_pos() const;
    // get the velocity <vx, vy> of bird
    std::pair<double, double> get_v() const;
    // get the acceleration <ax, ay> of bird
    std::pair<double, double> get_a() const;
    // set the position <x, y> of bird
    void set_pos(int _x, int _y);
    // set the velocity <vx, vy> of bird
    void set_v(double _vx, double _vy);
    // set the acceleration <ax, ay> of bird
    void set_a(double _ax, double _ay);

private:
    // x, y represent the coordinate of the bird
    // vx, vy represent the velocity of the bird
    // ax, ay represent the acceleration of the bird
    double x, y, vx, vy, ax, ay;
};
#endif