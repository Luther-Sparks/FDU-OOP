#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <set>
#include <numeric>
#include <unordered_map>
using namespace std;

vector<string> words;
vector<string> n_grams;
unordered_map<string, int> n_gram_count;
vector<vector<int>> n_gram_matrix;
vector<vector<float>> normalized_matrix;

vector<vector<int>> get_n_gram_matrix(vector<string>& words, vector<string>& n_grams, const string& filename, int n) {
    ifstream file;
    file.open(filename);
    cout << "Reading file " << filename << "..." << endl;
    assert(file.is_open());
    string all_text;
    int counter = 0;
    while (getline(file, all_text)) {
        transform(all_text.begin(), all_text.end(), all_text.begin(), ::tolower);

        // 可以不用正则而用字符串分割
        regex word_regex("\\s");
        sregex_token_iterator regex_iter(all_text.begin(), all_text.end(), word_regex, -1);
        sregex_token_iterator end;
        while (regex_iter != end) {
            words.emplace_back(*regex_iter);
            ++regex_iter;
        }
    }

    for (int i = 0; i < n - 1; i++) {   // padding
        words.insert(words.begin(), "");
        words.insert(words.end(), "");
    }

    vector<string>::iterator iter, iter_end;
    for (iter = words.begin(), iter_end = iter+n-1; iter_end != words.end(); iter++, iter_end++) {
        counter++;
        if (counter % 1000 == 0) {
            cout << "epoch: " << counter / 1000 << endl;
        }
        string n_gram = accumulate(iter, iter_end, string(""), [](string& s, string& t) {
            return s + " " + t;
        });
        n_grams.emplace_back(n_gram);
        n_gram_count[*iter_end+" "+n_gram]++;
    }
    cout << "Done with setting up words and n_grams." << endl;
    cout << "Now setting up n_gram_matrix..." << endl;
    counter = 0;
    auto n_grams_set = set<string>(n_grams.begin(), n_grams.end());
    n_grams = vector<string>(n_grams_set.begin(), n_grams_set.end());
    auto words_set = set<string>(words.begin(), words.end());
    words = vector<string>(words_set.begin(), words_set.end());
    int n_gram_num = n_grams.size();
    int n_words = words.size();
    cout << "words.size(): " << words.size() << '\t' << "n_grams.size(): " << n_grams.size() << endl;
    n_gram_matrix = decltype(n_gram_matrix)(words.size(), vector<int>(n_grams.size(), 0));
    cout << "n_gram_matrix.size(): [" << n_gram_matrix.size() << ", " << n_gram_matrix[0].size() << "]" << endl;
    n_gram_matrix[0][0] = 0;
    cout << "Done with filtering words and n_grams." << endl;
    for (int i = 0; i < n_words; i++) {
        counter++;
        if (counter % 1000 == 0) {
            cout << "epoch: " << counter << endl;
        }
        for (int j = 0; j < n_gram_num; j++) {
            auto iter = n_gram_count.find(words[i]+" "+n_grams[j]);
            if (iter != n_gram_count.end()) {
                n_gram_matrix.at(i).at(j) = iter->second;
            }
            else {
                n_gram_matrix.at(i).at(j) = 0;
            }
        }
    }
    file.close();
    return n_gram_matrix;
}

vector<vector<float>> normalize(vector<vector<int>>& matrix) {
    normalized_matrix = decltype(normalized_matrix)(matrix.size(), vector<float>(matrix[0].size(), 0.0));
    for (int i = 0; i < matrix.size(); i++) {
        float row_sum = accumulate(matrix[i].begin(), matrix[i].end(), 0.0);
        for (int j = 0; j < matrix[0].size(); j++) {
            normalized_matrix[i][j] = (float)matrix[i][j] / row_sum;
        }
    }
    return normalized_matrix;
}


int main(int argc, const char** argv) {
    // if (argc != 3) {
    //     cout << "Invalid input" << endl;
    //     cout << "Usage: ./n-gram <n> <input file>" << endl;
    //     return 1;
    // }
    n_gram_matrix = get_n_gram_matrix(words, n_grams, "wiki.txt", 2);
    auto normalized_matrix = normalize(n_gram_matrix);
    for(auto gram : n_grams) {
        cout << '\t' << gram;
    }
    cout << endl;
    for (int i = 0; i < words.size(); i++) {
        cout << words[i];
        for (int j = 0; j < n_grams.size(); j++) {
            cout << '\t' << normalized_matrix[i][j];
        }
        cout << endl;
    }
    return 0;
}