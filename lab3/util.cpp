#include "util.h"
// You can include any std header file here.
#include <regex>

using namespace std;

/**
 * @brief split a string by the delimiter space aka ` ` and append the result to the back of the vector `ret`.
 * 
 * @param s the string to be splitted
 * @param ret result vector. In this lab, argument `ret` is a global variable 
 *            and is used to store the words according to the appearance order.
 */
void spilt_string(const string& s, vector<string>& ret) {
    // hint: you can use function `substr` to get a substring of the string `s`
    //       if you know what regular expression is, you can use `regex` to easily split the string `s`
    // TODO: implement this function
    /* Your code here */
    regex word_regex("\\s");
    sregex_token_iterator regex_iter(s.begin(), s.end(), word_regex, -1);
    sregex_token_iterator end;
    while (regex_iter != end) {
        ret.emplace_back(*regex_iter);
        ++regex_iter;
    }
    return;
}
