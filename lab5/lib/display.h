#ifdef _WIN32
#include "curses.h"
#else
#include <ncurses.h>
#endif
#include <chrono>
#include <string>

class Display {
    /**
     * @brief This is the class for the display in terminal. 
     * Each application should only have ONE display object.
     * We can use this object to draw things on the screen.
     */
   public:
    // If rows and cols are not specified, use the values from the terminal
    Display(); 
    
    // Use the specified values to initialize the display
    Display(int rows, int cols); 
    
    // When the object is destroyed, the curses library will be closed
    ~Display();

    // Return the number of columns
    int get_cols() const;
    // Return the number of rows
    int get_rows() const; 

    // Put a string on the screen at (x, y)
    // e.g (0, 0) is the top left corner and (0, get_cols() - 1) is the top right corner
    void put_string(int x, int y, std::string str); 

    // Force refresh the screen, this function should be called after any changes to the screen
    // If not called, the changes might not be shown on the screen immediately
    // e.g put_string(0,1,"a");put_string(0,2,"b");refresh();
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
    

   private:
    int lines, cols;
    int ch;
    WINDOW* win;
    std::chrono::time_point<std::chrono::system_clock> time_start;
};
