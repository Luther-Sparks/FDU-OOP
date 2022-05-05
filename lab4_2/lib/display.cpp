#include "display.h"

#include <thread>

Display::Display(std::string log_file_name) : plog_file(nullptr) {
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
    if (log_file_name != "") {
        plog_file = new std::ofstream(log_file_name);
    }
    screen.resize(lines);
    for (int i = 0; i < lines; i++) {
        screen[i].resize(cols);
        for (int j = 0; j < cols; j++) {
            screen[i][j] = ' ';
        }
    }
    buffer = screen;
}

Display::Display(int rows, int cols, std::string log_file_name)
    : lines(rows), cols(cols), plog_file(nullptr) {
    initscr();             // Initialize ncurses
    noecho();              // Don't echo input
    cbreak();              // Don't wait for ENTER
    keypad(stdscr, TRUE);  // Enable arrow keys
    curs_set(0);           // Hide cursor
    ch = -1;
    time_start = std::chrono::system_clock::now();
    win = newwin(rows, cols, 0, 0);  // Create window
    wrefresh(win);                   // Refresh window
    if (log_file_name != "") {
        plog_file = new std::ofstream(log_file_name);
    }
    screen.resize(lines);
    for (int i = 0; i < lines; i++) {
        screen[i].resize(cols);
        for (int j = 0; j < cols; j++) {
            screen[i][j] = ' ';
        }
    }
    buffer = screen;
}

Display::~Display() {
    delwin(win);  // Delete window
    endwin();     // End ncurses
    if (plog_file != nullptr) {
        plog_file->close();
        delete plog_file;
    }
}

int Display::get_rows() const { return lines; }
int Display::get_cols() const { return cols; }

void Display::refresh() {
    wrefresh(win);
    screen = buffer;
}

void Display::clear() {
    wclear(win);
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < cols; j++) {
            buffer[i][j] = ' ';
        }
    }
}

void Display::put_string(int x, int y, std::string str) {
    mvwprintw(win, y, x, str.c_str());  // Print string
    for (int i = 0; i < (int)str.size(); i++) {
        set_buffer(x + i, y, str[i]);
    }
}

void Display::put_vertical_line(int x, int y, int l, int ch) {
    mvwvline(win, y, x, ch, l);
    for (int i = 0; i < l; i++) {
        set_buffer(x, y + i, ch);
    }
}

void Display::put_horizontal_line(int x, int y, int l, int ch) {
    mvwhline(win, y, x, ch, l);
    for (int i = 0; i < l; i++) {
        set_buffer(x + i, y, ch);
    }
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

void Display::sleep(int millisecond) {
    std::this_thread::sleep_for(std::chrono::milliseconds(millisecond));
}

int Display::time() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now() - time_start)
        .count();
}

void Display::log(std::string str, bool print_screen) {
    if (plog_file == nullptr) {
        return;
    }
    *plog_file << "[" << time() << "] " << str << std::endl;
    if (!print_screen) {
        return;
    }
    for (const auto& line : screen) {
        for (auto ch : line) {
            *plog_file << ch;
        }
        *plog_file << std::endl;
    }
}

bool Display::set_buffer(int x, int y, int ch) {
    if (x < 0 || x >= cols || y < 0 || y >= lines) {
        return false;
    }
    buffer[y][x] = ch;
    return true;
}