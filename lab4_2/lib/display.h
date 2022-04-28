#ifndef DISPLAY_GUARD
#define DISPLAY_GUARD
#ifdef _WIN32
#include "curses.h"
#else
#include <ncurses.h>
#endif
#include <chrono>
#include <fstream>
#include <string>
#include <vector>


class Display {
    /**
     * @brief This is the class for the display in terminal.
     * Each application should only have ONE display object.
     * We can use this object to draw things on the screen.
     */
   public:
    // If rows and cols are not specified, use the values from the terminal
    Display(std::string log_file_name = "");

    // Use the specified values to initialize the display
    Display(int rows, int cols, std::string log_file_name = "");

    // When the object is destroyed, the curses library will be closed
    ~Display();

    // Return the number of columns
    int get_cols() const;
    // Return the number of rows
    int get_rows() const;

    // Put a string on the screen at (x, y)
    // e.g (0, 0) is the top left corner and (0, get_cols() - 1) is the top
    // right corner
    void put_string(int x, int y, std::string str);

    // Put a vertical line on the screen at (x, y), with length l, and character
    // c
    void put_vertical_line(int x, int y, int l, int ch);

    // Put a horizontal line on the screen at (x, y), with length l, and
    // character c
    void put_horizontal_line(int x, int y, int l, int ch);

    // Force refresh the screen, this function should be called after any
    // changes to the screen If not called, the changes might not be shown on
    // the screen immediately e.g
    // put_string(0,1,"a");put_string(0,2,"b");refresh();
    void refresh();

    // Clear the screen
    void clear();

    // Get a character from the keyboard
    // This is wide-char instead of char(ASCII), so we can use the arrow keys
    // If timeout is -1, this function will wait until a character is pressed
    // If timeout > 0, this function will wait for timeout milliseconds
    // And return -1*last_key_pressed if timeout is reached
    // Other inputs are undefined behavior
    int get_char(int timeout = -1);

    // Sleep for millisecond milliseconds
    void sleep(int millisecond);

    // Return the number of milliseconds since the program started
    int time();

    // Log the current string to the log file
    // If log_file_name is empty, nothing will be logged
    // Else, we clear the log file when initializing the display
    // and append the current time, the screen and the string each time we call
    // e.g.
    // [3.23] string
    // screen
    void log(std::string str = "", bool print_screen = true);

   private:
    int lines, cols;
    int ch;
    std::vector<std::vector<char>> screen;
    std::vector<std::vector<char>> buffer;
    std::ofstream* plog_file;
    WINDOW* win;
    std::chrono::time_point<std::chrono::system_clock> time_start;
    bool set_buffer(int x, int y, int ch);
};

#endif // !DISPLAY_GUARD