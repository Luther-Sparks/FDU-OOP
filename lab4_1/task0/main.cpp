#include "../lib/display.h"

int main(){
    auto display = Display();
    display.put_string(display.get_cols()/2, display.get_rows()/2, "Hello, world!");
    // TODO: put a "I love OOP" on the bottom of the screen
    // Your code starts here
    // Your code ends here
    display.refresh();
    display.get_char(); // Wait until press the key
    return 0;
}