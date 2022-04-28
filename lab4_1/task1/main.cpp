#include "../lib/display.h"

void main_loop(Display &display) {
    int lines = display.get_rows();
    int cols = display.get_cols();
    int line = lines / 2;
    int col = cols / 2;
    display.put_string(col, line, "#");
    display.put_string(cols / 2 - 7, 0, "lonely wanderer");
    display.refresh();
    while (true) {
        int ch = display.get_char();
        display.clear();
        display.put_string(cols / 2 - 7, 0, "lonely wanderer");
        display.put_string(cols / 2, lines - 1, std::to_string(ch));
        // Now, if the wanderer walk to the border, the wanderer will walk through the border and appear on the other side of the screen. 
        // We want the wanderer to appear on a random position on the screen.
        // TODO: Please modify the code below to implement this feature.
        /* Your code here */
        if (ch == 'q') {
            break;
        } else if (ch == 'w') {
            line = (line - 1 + lines) % lines;
        } else if (ch == 's') {
            line = (line + 1) % lines;
        } else if (ch == 'a') {
            col = (col - 1 + cols) % cols;
        } else if (ch == 'd') {
            col = (col + 1) % cols;
        }
        display.put_string(col, line, "#");
        display.refresh();
        display.sleep(25);
    }
}

int main() {
    auto display = Display();
    main_loop(display);
}
