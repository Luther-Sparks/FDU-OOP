#ifdef _WIN32
#include "../lib/curses.h"
#else
#include <ncurses.h>
#endif

#include <iostream>
#include <string>
using namespace std;
void draw_hello_world() {
    // Set cursor to (middle of screen, middle of screen)
    // Draw a box around the text
    string s = "#Welcome to this new lab!#";
    string boundry = "##########################";
    move(LINES / 2 - 1, COLS / 2 - s.length() / 2);
    printw(boundry.c_str());
    move(LINES / 2, COLS / 2 - s.length() / 2);
    printw(s.c_str());
    move(LINES / 2 + 1, COLS / 2 - s.length() / 2);
    printw(boundry.c_str());
}
int main() {
    // Initialize ncurses
    initscr();
    // Draw hello world
    draw_hello_world();
    // Wait for user input
    getch();
    // End ncurses
    endwin();
    return 0;
}