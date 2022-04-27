#include "object.h"




class Rectangle : public Object {
   public:
    Rectangle(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}
    ~Rectangle() = default;
    void draw(Display& display) const override;
    void tick(int dx, int dy) override;
    bool is_inside(int x, int y) const override;
    Type type() const override { return Type::Rectangle; }
    bool in_screen(Object& border) override;
    bool if_collide(Object& obj) override;

   protected:
    int x;       // x coordinate of the top left corner
    int y;       // y coordinate of the top left corner
    int width;   // width of the rectangle (in x direction)
    int height;  // height of the rectangle (in y direction)
};