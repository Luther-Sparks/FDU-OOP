#ifdef _WIN32
#include "curses.h"
#else
#include <ncurses.h>
#endif
#include <chrono>
#include <string>

class Display {
   public:
    Display();
    Display(int rows, int cols);
    ~Display();

    int get_rows() const;
    int get_cols() const;

    void put_string(int x, int y, std::string str);
    void refresh();
    void clear();
    int get_char(int timeout = -1);
    void sleep(int millisecond);
    int time();

   private:
    int lines, cols;
    int ch;
    WINDOW* win;
    std::chrono::time_point<std::chrono::system_clock> time_start;
};
