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
    // TODO: detect collision between each pair of objects
    /* Your code here */
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
    display.sleep(200);
    display.get_char();
}

void add_rectangle(ObjPool& pool, Display& d) {
    // TODO: add a moving_rectangle to the pool
    /* Your code here */
}

int main() {
    Display d("log.txt");
    string audio_dir = "../audio/";
    ObjPool obj_pool;
    Bird* bird = new Bird(d.get_cols() / 2, d.get_rows() / 2, 0, 0, 0, 0);
    Border* border = new Border(0, 0, d.get_cols(), d.get_rows());
    obj_pool.emplace_back(bird);
    obj_pool.emplace_back(border);

    while (true) {
        // Process keyboard input
        int c = d.get_char(50);
        d.clear();
        if (c == 'q') {
            break;
        } else if (c == ' ') {
        }

        // Add new rectangle
        add_rectangle(obj_pool, d);

        // Update object state
        for (auto& obj : obj_pool) {
            obj->tick(c);
        }

        // Detect collision
        detect_collision(obj_pool);

        //TODO: Process invalid object
        /* Your code here */

        //TODO: Bird collide with border
        /* Your code here */

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