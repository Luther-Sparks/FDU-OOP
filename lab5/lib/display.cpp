#include "display.h"

#include <thread>

Display::Display() {
    initscr();             // Initialize ncurses
    noecho();              // Don't echo input
    cbreak();              // Don't wait for ENTER
    keypad(stdscr, TRUE);  // Enable arrow keys
    curs_set(0);           // Hide cursor
    lines = LINES;
    cols = COLS;
    ch = -1;
    time_start = std::chrono::system_clock::now();
    win = newwin(LINES, COLS, 0, 0);  // Create window
    wrefresh(win);                    // Refresh window
}

Display::Display(int rows, int cols) : lines(rows), cols(cols) {
    initscr();             // Initialize ncurses
    noecho();              // Don't echo input
    cbreak();              // Don't wait for ENTER
    keypad(stdscr, TRUE);  // Enable arrow keys
    curs_set(0);           // Hide cursor
    ch = -1;
    // Get time in second
    time_start = std::chrono::system_clock::now();
    win = newwin(rows, cols, 0, 0);  // Create window
    wrefresh(win);                    // Refresh window
}

Display::~Display() {
    delwin(win);  // Delete window
    endwin();     // End ncurses
}

int Display::get_rows() const { return lines; }
int Display::get_cols() const { return cols; }

void Display::refresh() { wrefresh(win); }

void Display::clear() { wclear(win); }

void Display::put_string(int x, int y, std::string str) {
    mvwprintw(win, y, x, str.c_str());  // Print string
}

int Display::get_char(int timeout) {
    wtimeout(win, timeout);
    int result = wgetch(win);
    wtimeout(win, -1);
    if (result < 0) {
        return -ch;
    }
    ch = result;
    return result;
}

void Display::sleep(int millisecond) { std::this_thread::sleep_for(std::chrono::milliseconds(millisecond)); }

int Display::time() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - time_start).count();
}