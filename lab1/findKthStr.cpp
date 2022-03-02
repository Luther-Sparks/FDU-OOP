#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<string> StrVec;

StrVec FindKthStr(StrVec str_vec, int k) {
    StrVec res;
    sort(str_vec.begin(), str_vec.end(), [](string a, string b) {
        return a.size() < b.size();
    });
    size_t length = 0x7fffffff;
    auto iter = str_vec.begin();
    for (; iter != str_vec.end(); iter++) {
        if (length != iter->size()) {
            length = iter->size();
            k--;
        }
        if (!k) break;
    }
    while (iter->size() == length) {
        res.emplace_back(*iter);
        iter++;
    }
    return res;
}

int main() {
    int n, k;
    cin >> n >> k;
    StrVec str_vec;
    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;
        str_vec.emplace_back(str);
    }
    StrVec res = FindKthStr(str_vec, k);
    for (auto str : res) {
        cout << str << endl;
    }
    return 0;
}