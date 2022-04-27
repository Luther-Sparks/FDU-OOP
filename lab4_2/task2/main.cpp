#include "../lib/display.h"
#ifndef __SRC_FILE
#define __SRC_FILE
#endif // !__SRC_FILE
#include "../lib/audio.h"
#include "../game/rectangle.h"
#include "bird.h"
#include <vector>

using std::vector;
using ObjPool = vector<Object*>;

const double g = 0.1;
const double v_tap_up = -1;
const double v_tap_left = -1;
const double a_tap_left = 0.1;
const double v_tap_right = 1;
const double a_tap_right = -0.1;

void detect_collision(ObjPool& pool, Object* _border) {
    for (size_t i = 0; i < pool.size(); ++i) {
        pool[i]->in_screen(*_border);
        for (size_t j = i + 1; j < pool.size(); ++j) {
            if (pool[i]->type() == Type::Bird && pool[j]->type() == Type::Rectangle) {
                if (pool[i]->if_collide(*pool[j])) {
                    break;
                }
            }
        }
    }
}

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
    Audio bgm(audio_dir+"bgm.mp3");
    bgm.play_loop();
    Audio flap(audio_dir+"flap.mp3");
    Audio collide(audio_dir+"collide.mp3");
    Audio game_over(audio_dir+"applause.mp3");
    

    ObjPool obj_pool;
    Bird* bird = new Bird(d.get_cols() / 2, d.get_rows() / 2, 0, 0, 0, 0);
    Rectangle* _border = new Rectangle(0, 0, d.get_cols(), d.get_rows());
    obj_pool.emplace_back(bird);
    int c;
    int count = 0;
    int lastc = 0;
    try {
        while (true) {
            count = (count + 1) % 30;
            if (!count) {
                int x = d.get_cols() - 3;
                int y = rand() % d.get_rows();
                int w = rand() % 2 + 1;
                int h = rand() % (2 * (d.get_rows() - y) / 3) + 1;
                obj_pool.emplace_back(new Rectangle(x, y, w, h));
            }
            c = d.get_char(50);
            d.clear();
            auto pos = bird->get_pos();
            auto v = bird->get_v();
            auto a = bird->get_a();
            if (c == 'q') {
                break;
            } else if (c == ' ') {
                if (lastc != c) {
                    d.log("space");
                    flap.play_once();
                }
                bird->set_v(v.first, v_tap_up);
                bird->set_a(a.first, g);
            } else if (c == 'z') {
                bird->set_v(v_tap_left, v.second);
                bird->set_a(a_tap_left, g);
            } else if (c == 'x') {
                bird->set_v(v_tap_right, v.second);
                bird->set_a(a_tap_right, g);
            } else {
                if ((v.first + a.first) * a.first >= 0) {
                    bird->set_a(0, g);
                    bird->set_v(0, v.second);
                } else {
                    bird->set_a(a.first, g);
                }
            }

            d.put_string(1, 1, "Time: " + std::to_string(d.time() / 1000.0));
            d.put_string(1, 2, "Keystrock: " + std::to_string(c));
            d.put_string(1, 3, "Pos: " + std::to_string(pos.first) + "," + std::to_string(pos.second));
            d.put_string(1, 4, "Speed: " + std::to_string(v.first) + "," + std::to_string(v.second));
            d.put_string(1, 5, "Acceleration: " + std::to_string(a.first) + "," + std::to_string(a.second));
            d.refresh();
            d.log();
            for (auto& obj : obj_pool) {
                if (obj->type() == Type::Bird) {
                    obj->tick(0, 0);
                } else {
                    obj->tick(v_tap_left, 0);
                }
            }
            detect_collision(obj_pool, _border);
            for (auto it = obj_pool.begin(); it != obj_pool.end(); it++) {
                if (!(*it)->get_valid()) {
                    if ((*it)->type() == Type::Rectangle) {
                        it = obj_pool.erase(it);
                    }
                }
            }
            if (!bird->get_valid()) {
                collide.play_once();
                bgm.stop();
                game_over.play_once();
                show_game_over(d, d.time() / 1000.0);
                game_over.stop();
                collide.stop();
                flap.stop();
                break;
            }
            for (auto& obj : obj_pool) {
                obj->draw(d);
            }
            lastc = c;
        }
    } catch (std::exception& e) {
        d.log(e.what());
        bgm.stop();
    }
    return 0;
}