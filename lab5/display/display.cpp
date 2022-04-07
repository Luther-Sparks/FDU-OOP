#include "display.h"

#include <chrono>
#include <thread>

Display::Display() {
    initscr();             // Initialize ncurses
    noecho();              // Don't echo input
    cbreak();              // Don't wait for ENTER
    keypad(stdscr, TRUE);  // Enable arrow keys
    curs_set(0);           // Hide cursor
    lines = LINES;
    cols = COLS;
    win = newwin(LINES, COLS, 0, 0);  // Create window
    wrefresh(win);                    // Refresh window
}

Display::Display(int lines, int cols) : lines(lines), cols(cols) {
    initscr();                        // Initialize ncurses
    noecho();                         // Don't echo input
    cbreak();                         // Don't wait for ENTER
    keypad(stdscr, TRUE);             // Enable arrow keys
    curs_set(0);                      // Hide cursor
    win = newwin(lines, cols, 0, 0);  // Create window
    wrefresh(win);                    // Refresh window
}

Display::~Display() {
    delwin(win);  // Delete window
    endwin();     // End ncurses
}

void Display::refresh() { wrefresh(win); }

void Display::clear() { wclear(win); }

void Display::put_string(int x, int y, std::string str) {
    mvwprintw(win, y, x, str.c_str());  // Print string
}

int Display::get_char() { return wgetch(win); }

void Display::sleep(int millisecond) {
    std::this_thread::sleep_for(std::chrono::milliseconds(millisecond));
}