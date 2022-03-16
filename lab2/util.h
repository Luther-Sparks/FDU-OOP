#ifndef UTIL_H
#define UTIL_H
#include <string>
#include <vector>
using namespace std;

vector<string> split(const string &str, char delim);
ostream& output_info(ostream& os, const string& str);
ostream& output_error(ostream& os, const string& str);

#endif