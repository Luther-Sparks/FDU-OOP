#include "../lib/display.h"
#ifndef __SRC_FILE
#define __SRC_FILE
#endif // !__SRC_FILE
#include "../lib/audio.h"
#include "../game/rectangle.h"
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
    Display d("log.txt");
    string audio_dir = "../audio/";
    string bgm_file = audio_dir + "bgm.mp3";
    Audio bgm(bgm_file);
    bgm.play_loop();
    Bird bird(d.get_cols() / 2, d.get_rows() / 2, 0, 0, 0, 0);
    Rectangle border(0, 0, d.get_cols(), d.get_rows());
    int c;
    while (true) {
        c = d.get_char(50);
        d.clear();
        auto pos = bird.get_pos();
        auto v = bird.get_v();
        auto a = bird.get_a();
        if (c == 'q') {
            break;
        } else if (c == ' ') {
            bird.set_v(v.first, v_tap_up);
            bird.set_a(a.first, g);
        } else if (c == 'z') {
            bird.set_v(v_tap_left, v.second);
            bird.set_a(a_tap_left, g);
        } else if (c == 'x') {
            bird.set_v(v_tap_right, v.second);
            bird.set_a(a_tap_right, g);
        } else {
            if ((v.first + a.first) * a.first >= 0) {
                bird.set_a(0, g);
                bird.set_v(0, v.second);
            } else {
                bird.set_a(a.first, g);
            }
        }

        d.put_string(1, 1, "Time: " + std::to_string(d.time() / 1000.0));
        d.put_string(1, 2, "Keystrock: " + std::to_string(c));
        d.put_string(1, 3, "Pos: " + std::to_string(pos.first) + "," + std::to_string(pos.second));
        d.put_string(1, 4, "Speed: " + std::to_string(v.first) + "," + std::to_string(v.second));
        d.put_string(1, 5, "Acceleration: " + std::to_string(a.first) + "," + std::to_string(a.second));
        d.refresh();
        d.log();
        bird.tick(0, 0);
        if (!bird.in_screen(border)) {
            bgm.stop();
            Audio game_over(audio_dir + "applause.mp3");
            game_over.play_once();
            show_game_over(d, d.time() / 1000.0);
            break;
        }
        bird.draw(d);
        border.draw(d);
    }
}