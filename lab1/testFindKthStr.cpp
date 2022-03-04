#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

using namespace std;

typedef vector<string> StrVec;

bool check_StrVec_equal(StrVec a, StrVec b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

bool test(StrVec str_vec, int k, StrVec expected) {
    ofstream fin("tmp.in");
    fin << str_vec.size() << endl;
    fin << k << endl;
    for (auto str : str_vec) {
        fin << str << endl;
    }
    fin.close();
    #ifdef _WIN32
    system(".\\build\\findKthStr.exe < tmp.in > tmp.out");
    #else
    system("touch tmp.in");
    system("./build/findKthStr < tmp.in > tmp.out");
    #endif
    ifstream fout("tmp.out");
    string str;
    StrVec res;
    while (getline(fout, str)) {
        regex word_regex("\\s");
        sregex_token_iterator regex_iter(str.begin(), str.end(), word_regex, -1);
        sregex_token_iterator end;
        while (regex_iter != end) {
            res.emplace_back(*regex_iter);
            ++regex_iter;
        }
    }
    fout.close();
    #ifdef _WIN32
    system("del tmp.in tmp.out");
    #else
    system("rm tmp.in tmp.out");
    #endif
    if (!check_StrVec_equal(res, expected)) {
        return false;
    }
    return true;
}

int invalid_k_test() {
    StrVec vec = {
        "php", "is", "the", "best", "language", "in", "the", "world"
    };
    cout << "running invalid_k_test..." << endl;
    bool res = test(vec, -1, StrVec({})) && test(vec, 0, StrVec({})) && test(vec, 7, StrVec({}));
    if (!res) {
        cout << "\033[31m" << "invalid_k_test failed" << "\033[0m" << endl;
        return 0;
    }
    cout << "\033[32m" << "invalid_k_test passed" << "\033[0m" << endl;
    return 5;
}

int single_output_test() {
    StrVec vec = {
        "php", "is", "the", "best", "language", "in", "the", "world"
    };
    cout << "running single_output_test..." << endl;
    bool res = test(vec, 3, StrVec({"best"})) && test(vec, 5, StrVec({"language"}));
    if (!res) {
        cout << "\033[31m" << "single_output_test failed" << "\033[0m" << endl;
        return 0;
    }
    cout << "\033[32m" << "single_output_test passed" << "\033[0m" << endl;
    return 5;
}

int multi_output_test() {
    StrVec vec = {
        "php", "is", "the", "best", "language", "in", "the", "world"
    };
    cout << "running multi_output_test..." << endl;
    bool res = test(vec, 2, StrVec({"php", "the", "the"})) && test(vec, 1, StrVec({"is", "in"}));
    if (!res) {
        cout << "\033[31m" << "multi_output_test failed" << "\033[0m" << endl;
        return 0;
    }
    cout << "\033[32m" << "multi_output_test passed" << "\033[0m" << endl;
    return 10;
}

int main() {
    int score = 0;
    cout << "running all tests..." << endl;
    score += invalid_k_test();
    score += single_output_test();
    score += multi_output_test();
    cout << "total score of this part: " << score << endl;
    return 0;
}
