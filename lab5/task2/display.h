#include <ncurses.h>

#include <string>
class Display {
   public:
    Display();
    Display(int lines, int cols);
    ~Display();

    int get_lines() const { return lines; }
    int get_cols() const { return cols; }

    void put_string(int x, int y, std::string str);
    void refresh();
    void clear();
    int get_char();

   private:
    int lines, cols;
    WINDOW* win;
};
