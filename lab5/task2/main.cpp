#include "../lib/display.h"
#include "bird.h"
const double g = 0.1;
const double v_tap_up = -1;
const double v_tap_left = -1;
const double a_tap_left = 0.1;
const double v_tap_right = 1;
const double a_tap_right = -0.1;

void show_game_over(Display &display, double second) {
    display.clear();
    display.put_string(display.get_cols() / 2 - 7, display.get_rows() / 2 - 1, "Game Over");
    display.put_string(display.get_cols() / 2 - 14, display.get_rows() / 2,
                       "Bird survives " + std::to_string(second) + " seconds");
    display.put_string(display.get_cols() / 2 - 13, display.get_rows() / 2 + 1, "Press any key to exit");
    display.refresh();
    display.sleep(200);
    display.get_char();
}
int main() {
    Display d;
    Bird bird(d.get_cols() / 2, d.get_rows() / 2, 0, 0, 0, 0);
    int c;
    while (true) {
        c = d.get_char(50);
        d.clear();
        auto pos = bird.get_pos();
        auto v = bird.get_v();
        auto a = bird.get_a();
        // You should read notes carefully and think what operation you should do to make sure it flies successfully.
        // Press `q` will quit the game. Press ` `(aka space) will make the bird fly up.
        // Press `x` will make the bird fly right while `z` will make the bird fly left.
        // hint: you should probably read task1 first to get to know how to control your bird.
        // TODO: fill this blank with your code and make sure it works.



        d.put_string(0, 0, "Time: " + std::to_string(d.time() / 1000.0));
        d.put_string(0, 1, "Keystrock: " + std::to_string(c));
        d.put_string(0, 2, "Pos: " + std::to_string(pos.first) + "," + std::to_string(pos.second));
        d.put_string(0, 3, "Speed: " + std::to_string(v.first) + "," + std::to_string(v.second));
        d.put_string(0, 4, "Acceleration: " + std::to_string(a.first) + "," + std::to_string(a.second));

        d.put_string(pos.first, pos.second, "@");

        d.refresh();

        if (pos.second <= 0 || pos.second >= d.get_rows() - 1 || pos.first <= 0 || pos.first >= d.get_cols() - 1) {
            show_game_over(d, d.time() / 1000.0);
            break;
        }

        bird.tick();
    }
}
