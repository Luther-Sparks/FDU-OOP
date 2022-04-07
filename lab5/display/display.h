#include <ncurses.h>

#include <string>
class Display {
   public:
    Display();
    Display(int lines, int cols);
    ~Display();

    int get_rows() const { return lines; }
    int get_cols() const { return cols; }

    void put_string(int x, int y, std::string str);
    void refresh();
    void clear();
    int get_char(int timeout = -1);
    void sleep(int millisecond);

   private:
    int lines, cols;
    WINDOW* win;
};
