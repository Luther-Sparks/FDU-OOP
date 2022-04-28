#ifndef OBJECT_GUARD
#define OBJECT_GUARD

#include "../lib/display.h"
#include <map>
#include <string>

enum class Type {
    Rectangle,
    Bird,
    Border,
};

class Object {
    public:
        Object() = default;
        ~Object() = default;
        // Draws the object to the screen
        virtual void draw(Display& display) const = 0;
        // Updates the object every frame (that's why it's called tick) based on the keyboard input
        virtual void tick(int key) = 0;
        // Return whether the (x,y) coordinates are inside the object
        virtual bool is_inside(int x, int y) const = 0;
        // Return the type of the object
        virtual Type type() const = 0;
        // Return if this object collides with another object
        virtual bool detect_collide(Object& obj) = 0;
        bool get_valid() const { return valid; }
    protected:
        // Return if this object is valid 
        // If not, it will be removed from the game accordingly
        bool valid = true;
};

#endif // !OBJECT_GUARD
