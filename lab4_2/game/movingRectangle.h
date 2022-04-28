#ifndef MOVINGRECTANGLE_GUARD
#define MOVINGRECTANGLE_GUARD
#include "rectangle.h"

class MovingRectangle : public Rectangle {
   public:
    MovingRectangle(int x, int y, int width, int height, int dx, int dy);
    ~MovingRectangle() = default;
    void tick(int key) override;
   protected:
    int dx;
    int dy;
};
#endif