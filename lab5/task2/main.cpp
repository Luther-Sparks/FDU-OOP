#include <chrono>
#include <thread>

#include "display.h"
void main_loop(Display &display) {
    int lines = display.get_lines();
    int cols = display.get_cols();
    int line = lines / 2;
    int col = cols / 2;
    display.put_string(col, line, "#");
    display.put_string(cols/2-7, 0, "lonely wanderer");
    display.refresh();
    while (true) {
        int ch = display.get_char();
        display.clear();
        display.put_string(cols/2-7, 0, "lonely wanderer");
        display.put_string(cols / 2, lines - 1, std::to_string(ch));
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
        // Sleep 25ms
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
}

int main() {
    auto display = Display();
    main_loop(display);
}
