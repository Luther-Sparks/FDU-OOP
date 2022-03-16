#include "util.h"

#include <sstream>
using namespace std;

/**
 * @brief split string by delimiter
 * e.g "1,2,3,4" by "," => [1,2,3,4]
 * @param str any string
 * @param delim any char delimiter
 * @return vector<string> containing splitted string
 */
vector<string> split(const string& str, char delim) {
    vector<string> res;
    // TODO: complete this function
    /* Your Code Here */
    stringstream ss(str);
    string item;
    while (getline(ss, item, delim)) {
        res.push_back(item);
    }
    return res;
}

/**
 * @brief output info string to os and mark it green
 *
 * @param os any output stream, usually cout
 * @param str any string
 * @return ostream& the original output stream
 */
ostream& output_info(ostream& os, const string& str) {
    os << "\033[32m" << str << "\033[0m";
    return os.flush();
}

/**
 * @brief output error string to os and mark it red
 *
 * @param os any output stream, usually cerr
 * @param str any string
 * @return ostream& the original output stream
 */
ostream& output_error(ostream& os, const string& str) {
    os << "\033[31m" << str << "\033[0m";
    return os.flush();
}