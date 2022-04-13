#ifndef BIRD_GUARD
#define BIRD_GUARD
#include <utility>
class Bird {
   public:
    Bird() = default;
    Bird(double x, double y, double vx, double vy, double ax, double ay);
    Bird& operator=(const Bird&) = default;
    ~Bird() = default;

    void tick();
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