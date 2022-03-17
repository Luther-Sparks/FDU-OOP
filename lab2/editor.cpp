#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

#include "util.h"
using namespace std;

/**
 * @brief Read lines from filename
 * 
 * @param filename file to be opened
 * @param lines store each line of file
 * @return true if success
 * @return false if something goes wrong, e.g. os is not open
 */
bool read_lines(const string& filename, list<string> &lines) {
    ifstream is(filename);
    if (!is) {
        output_error(cerr, "Runtime error\n");
        return false;
    }
    lines.clear();
    string line;
    while (getline(is, line)) {
        lines.push_back(line);
    }
    return true;
}

/**
 * @brief Output lines to os.
 *
 * @param os output stream, usually cout or ofstream
 * @param lines
 * @param show_line_num if true, output line number before each line
 * @return true if success
 * @return false if something goes wrong, e.g. os is not open
 */
bool output_lines(ostream &os, const list<string> &lines, bool show_line_num = false) {
    if (!os) {
        output_error(cerr, "Runtime error\n");
        return false;
    }
    int i = 1;
    for (const string &line : lines) {
        if (show_line_num) {
            os << i++ << ": ";
        }
        os << line << endl;
    }
    return true;
}

/**
 * @brief Delete line at line_num from lines.
 *
 * @param lines The list of lines to be deleted from
 * @param line_num The index of the line to be delete.
 * @return true if the line is deleted successfully.
 * @return false something goes wrong, e.g. line_num is out of range.
 */
bool delete_line(list<string> &lines, int line_num) {
    if (line_num <= 0 || line_num > (int)lines.size()) {
        output_error(cerr, "Runtime error\n");
        return false;
    }
    auto it = lines.begin();
    advance(it, line_num - 1);
    lines.erase(it);
    return true;
}

/**
 * @brief Insert a line into the list of lines.
 *
 * @param lines The list of lines to be inserted into.
 * @param line_num The index of the line to be inserted.
 * @param line The line to be inserted.
 * @return true if the line is inserted successfully.
 * @return false something goes wrong, e.g. line_num is out of range.
 */
bool insert_line(list<string> &lines, int line_num, const string &line) {
    if (line_num <= 0 || line_num > (int)lines.size() + 1) {
        output_error(cerr, "Runtime error\n");
        return false;
    }
    auto it = lines.begin();
    advance(it, line_num - 1);
    lines.insert(it, line);
    return true;
}

/**
 * @brief
 *
 * @param lines The list of lines to be replaced.
 * @param line_num The index of the line to be replaced.
 * @param line The line to be replaced.
 * @return true if the line is replaced successfully.
 * @return false something goes wrong, e.g. line_num is out of range.
 */
bool replace_line(list<string> &lines, int line_num, const string &line) {
    if (line_num <= 0 || line_num > (int)lines.size()) {
        output_error(cerr, "Runtime error\n");
        return false;
    }
    auto it = lines.begin();
    advance(it, line_num - 1);
    *it = line;
    return true;
}

/**
 * @brief Check whether given argc is in expect_count
 *        E.g. check_argc(1, {1, 2, 3}) => true
 *             check_argc(2, {1, 3}) => false
 *        If in, return true, else output_error and return false
 *
 * @param argc the number of arguments
 * @param expect_count the expected number of arguments
 * @return true when argc is in expect_count otherwise false
 */
inline bool check_argc(vector<string>::size_type argc, vector<int> expect_count) {
    if (find(expect_count.begin(), expect_count.end(), argc) != expect_count.end()) {
        return true;
    }
    output_error(cerr, "Invalid command\n");
    return false;
}
/**
 * @brief A candy function to output ok
 *
 * @param result
 */
inline void check_result(bool result) {
    if (result) {
        output_info(cout, "OK\n");
    }
}

/**
 * @brief This is the main_loop function of the editor.
 *        It will parse the input from user and call the corresponding function.
 *        Valid commands are:
 *        1. i/insert [line_num] [line] // Insert [line] at [line_num], the
 * original line at [line_num] will be the next line.
 *        2. d/delete [line_num] // Delete [line_num]
 *        3. e/edit [line_num] [line] // Replace [line_num] with [line]
 *        4. l/list // List all lines with line number
 *        5. w/write [filename] // Write the file to [filename],
 *        if [filename] is not specified, we will use the original file name
 *        6. r/reload [filename] // Reload the file from [filename]
 *        if [filename] is not specified, we will use the original file name
 *        7. q/quit // Quit
 *
 *        Note:
 *        1. [line_num] is the line number, starting from 1.
 *        2. Both short and long command are supported.
 *           E.g. "i 1 hello" are equivalent to "insert 1 hello".
 *        3. If command is invalid including the number of the argument is
 *           invalid, it will call output_error(cerr, "Invalid command\n")
 *        4. If the command is executed successfully, it will call output_info(cout, "OK\n")
 *           Otherwise, it will call output_error(cerr, "Runtime error\n")
 *
 * @param is
 * @param filename
 */
void main_loop(const string &filename) {
    list<string> lines;
    read_lines(filename, lines);
    while (true) {
        cout << "> ";
        string cmd;
        getline(cin, cmd);
        vector<string> cmds = split(cmd, ' ', 3);
        if (cmds[0] == "i" || cmds[0] == "insert") {
            if (!check_argc(cmds.size(), {3})) continue;
            check_result(insert_line(lines, stoi(cmds[1]), cmds[2]));
        } else if (cmds[0] == "d" || cmds[0] == "delete") {
            if (!check_argc(cmds.size(), {2})) continue;
            check_result(delete_line(lines, stoi(cmds[1])));
        } else if (cmds[0] == "e" || cmds[0] == "edit") {
            if (!check_argc(cmds.size(), {3})) continue;
            check_result(replace_line(lines, stoi(cmds[1]), cmds[2]));
        } else if (cmds[0] == "l" || cmds[0] == "list") {
            if (!check_argc(cmds.size(), {1})) continue;
            check_result(output_lines(cout, lines, true));
        } else if (cmds[0] == "r" || cmds[0] == "reload") {
            if (!check_argc(cmds.size(), {1,2})) continue;
            string name = cmds.size() == 1 ? filename : cmds[1];
            check_result(read_lines(name, lines));
        } else if (cmds[0] == "w" || cmds[0] == "write") {
            if (!check_argc(cmds.size(), {1, 2})) continue;
            string name = cmds.size() == 1 ? filename : cmds[1];
            ofstream file(name);
            check_result(output_lines(file, lines));
            file.close();
        } else if (cmds[0] == "q" || cmds[0] == "quit") {
            if (!check_argc(cmds.size(), {1})) continue;
            break;
        } else {
            output_error(cerr, "Invalid command\n");
        }
    }
}