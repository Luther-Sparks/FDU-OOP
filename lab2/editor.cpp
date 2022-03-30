#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

#include "util.h"
using namespace std;

/**
 * @brief Read lines from filename
 *        If something goes wrong, also output_error(cerr, "Runtime error\n")
 * @param filename file to be opened
 * @param lines store each line of file
 * @return true if success
 * @return false if something goes wrong, e.g. can't open file
 */
bool read_lines(const string& filename, list<string> &lines) {
    // TODO: complete this function
    /* Your Code Here */
    
    return true;
}

/**
 * @brief Output lines to os.
 *        If something goes wrong, also output_error(cerr, "Runtime error\n")
 *
 * @param os output stream, usually cout or ofstream
 * @param lines lines to be output
 * @param show_line_num if true, output line number before each line
 * @return true if success
 * @return false if something goes wrong, e.g. os is not open
 */
bool output_lines(ostream &os, const list<string> &lines, bool show_line_num = false) {
    // TODO: complete this function
    /* Your Code Here */
    
    return true;
}

/**
 * @brief Delete line at line_num from lines.
 *        If something goes wrong, also output_error(cerr, "Runtime error\n")
 *
 * @param lines The list of lines to be deleted from
 * @param line_num The index of the line to be delete.
 * @return true if the line is deleted successfully.
 * @return false something goes wrong, e.g. line_num is out of range.
 */
bool delete_line(list<string> &lines, int line_num) {
    // TODO: complete this function
    /* Your Code Here */
    
    return true;
}

/**
 * @brief Insert a line into the list of lines.
 *        If something goes wrong, also output_error(cerr, "Runtime error\n")
 *
 * @param lines The list of lines to be inserted into.
 * @param line_num The index of the line to be inserted.
 * @param line The line to be inserted.
 * @return true if the line is inserted successfully.
 * @return false something goes wrong, e.g. line_num is out of range.
 */
bool insert_line(list<string> &lines, int line_num, const string &line) {
    // TODO: complete this function
    /* Your Code Here */
    
    return true;
}

/**
 * @brief Replace the line at line_num with line.
 *        If something goes wrong, also output_error(cerr, "Runtime error\n")
 *
 * @param lines The list of lines to be replaced.
 * @param line_num The index of the line to be replaced.
 * @param line The line to be replaced.
 * @return true if the line is replaced successfully.
 * @return false something goes wrong, e.g. line_num is out of range.
 */
bool replace_line(list<string> &lines, int line_num, const string &line) {
    // TODO: complete this function
    /* Your Code Here */
    
    return true;
}

/**
 * @brief Check whether given argc is in expect_count
 *        E.g. check_argc(1, {1, 2, 3}) => true
 *             check_argc(2, {1, 3}) => false
 *        If in, return true, else output_error(cerr, "Invalid command\n") and return false
 *
 * @param argc the number of arguments
 * @param expect_count the expected number of arguments
 * @return true when argc is in expect_count otherwise false
 */
inline bool check_argc(vector<string>::size_type argc, vector<int> expect_count) {
    // TODO: complete this function
    /* Your Code Here */
    
    return false;
}
/**
 * @brief If result is true, output_info(cout, "OK\n")
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
        } 
        //else if ...
        // TODO: complete this function
        /* Your Code Here */

    }
}