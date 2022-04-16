#include "../lib/display.h"
#include <map>
#include <string>

class Object {
    public:
        Object();
        ~Object();
        // Draws the object to the screen
        virtual void draw(Display& display) const = 0;
        // Updates the object every frame (that's why it's called tick) based on the global state map
        virtual void tick(std::map <std::string, std::string>& global_state) = 0;
        // Return whether the (x,y) coordinates are inside the object
        virtual bool is_inside(int x, int y) const = 0;
};
    