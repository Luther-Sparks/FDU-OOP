#ifndef BIRD_GUARD
#define BIRD_GUARD
class Bird {
   public:
    Bird() = default;
    Bird(double y, double speed, double acce);
    Bird& operator=(const Bird&) = default;
    ~Bird();
    void tick();
    int get_y() const;
    void set_v(double new_speed);

   private:
    double y;
    double speed, acce;
};
#endif