#ifndef EDITOR_H
#define EDITOR_H
#include <iostream>
#include <list>
#include <string>
using namespace std;
bool read_lines(const string& filename, list<string> &lines);
bool output_lines(ostream &os, const list<string> &lines, bool line_num = false);
bool delete_line(list<string> &lines, int line_num);
bool insert_line(list<string> &lines, int line_num, const string &line);
bool replace_line(list<string> &lines, int line_num, const string &line);
void main_loop(const string& filename);
#endif