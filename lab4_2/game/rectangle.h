#include "object.h"




class Rectangle : public Object {
   public:
    Rectangle(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}
    ~Rectangle() = default;
    void draw(Display& display) const override;
    void tick(std::map<std::string, std::string>& global_state) override;
    bool is_inside(int x, int y) const override;

   protected:
    int x;       // x coordinate of the top left corner
    int y;       // y coordinate of the top left corner
    int width;   // width of the rectangle (in x direction)
    int height;  // height of the rectangle (in y direction)
};