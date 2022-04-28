#include "../lib/display.h"
#ifndef __SRC_FILE
#define __SRC_FILE
#endif  // !__SRC_FILE
#include <vector>

#include "../game/border.h"
#include "../game/movingRectangle.h"
#include "../game/rectangle.h"
#include "../lib/audio.h"
#include "bird.h"

using std::vector;
using ObjPool = vector<Object*>;

void detect_collision(ObjPool& pool) {
    for (Object* obj1 : pool) {
        for (Object* obj2 : pool) {
            if (obj1 == obj2) continue;
            obj1->detect_collide(*obj2);
        }
    }
}

void show_game_over(Display& display, double second) {
    display.clear();
    display.put_string(display.get_cols() / 2 - 7, display.get_rows() / 2 - 1,
                       "Game Over");
    display.put_string(display.get_cols() / 2 - 14, display.get_rows() / 2,
                       "Bird survives " + std::to_string(second) + " seconds");
    display.put_string(display.get_cols() / 2 - 13, display.get_rows() / 2 + 1,
                       "Press any key to exit");
    display.refresh();
    display.get_char();
}

void add_rectangle(ObjPool& pool, Display& d) {
    static int count = 30;
    if (count-- > 0) return;
    count = 30;
    int y = rand() % (d.get_rows()-2)+1;
    int w = rand() % 5 + 1;
    int x = d.get_cols() - w;
    int h = rand() % (2 * (d.get_rows() - y) / 3) + 1;
    pool.push_back(new MovingRectangle(x, y, w, h, -1, 0));
}

int main() {
    Display d("log.txt");
    string audio_dir = "../audio/";
    Audio bgm(audio_dir + "bgm.mp3");
    bgm.play_loop();
    Audio flap(audio_dir + "flap.mp3");
    Audio collide(audio_dir + "collide.mp3");
    Audio game_over(audio_dir + "applause.mp3");
    ObjPool obj_pool;
    Bird* bird = new Bird(d.get_cols() / 2, d.get_rows() / 2, 0, 0, 0, 0);
    Border* border = new Border(0, 0, d.get_cols(), d.get_rows());
    obj_pool.emplace_back(bird);
    obj_pool.emplace_back(border);
    int lastc = 0;

    while (true) {
        // Process keyboard input
        int c = d.get_char(50);
        d.clear();
        if (c == 'q') {
            bgm.stop();
            flap.stop();
            collide.stop();
            game_over.stop();
            break;
        } else if (c == ' ') {
            if (lastc != c) {
                d.log("space");
                flap.play_once();
            }
        }
        lastc = c;

        // Add new rectangle
        add_rectangle(obj_pool, d);

        // Update object state
        for (auto& obj : obj_pool) {
            obj->tick(c);
        }

        // Detect collision
        detect_collision(obj_pool);

        // Process invalid object
        for (auto it = obj_pool.begin(); it != obj_pool.end(); it++) {
            if (!(*it)->get_valid() && (*it)->type() == Type::Rectangle) {
                delete *it;
                it = obj_pool.erase(it);
            }
        }

        // Bird collide with border
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

        // Draw objects
        for (auto& obj : obj_pool) {
            obj->draw(d);
        }
        d.put_string(1, 1, "Time: " + std::to_string(d.time() / 1000.0));
        d.put_string(1, 2, "Keystrock: " + std::to_string(c));
        d.refresh();
        d.log();
    }
    return 0;
}