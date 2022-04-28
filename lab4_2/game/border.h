#ifndef BORDER_GUARD
#define BORDER_GUARD
#include "rectangle.h"
class Border : public Rectangle {
public:
    Border(int x, int y, int width, int height);
    ~Border() = default;

    bool is_inside(int x, int y) const override;
    Type type() const override { return Type::Border; }
    bool detect_collide(Object& obj) override;
};


#endif