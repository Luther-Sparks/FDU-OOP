#include "grams.h"
#include "util.h"
#include <iostream>
#include <regex>
#include <set>
#include <numeric>

using namespace std;

// define some global variables
vector<string> words;                       // all words, sort by appearance order
vector<string> grams;                       // all grams, sort by appearance order
// for simplicity, each row of the co-occurrence matrix represents the word by lexicographical order
// thus, we'd use a map to store the index of the word which is `word_index`
map<string, int> word_index;                // index of word in co-occurrence matrix
vector<vector<int>> coocur_matrix;          // co-ocurrence martix, each row is a n-gram
vector<vector<double>> normalized_matrix;    // normalized co-ocurrence martix
// You can add more global variables here if you need.
// Notice that if you add more global variables, you should declare them in the `grams.h` using `extern`

/**
 * @brief read the input file and record all words in the file. 
 *  Store the words in the vector `words` according to the appearance order.
 * 
 * @param filename  file name of the input file
 * @param words     vector to store the words
 * @return size_t   the size of the `words` vector
 */
size_t record_words(const string& filename, vector<string>& words) {
    ifstream file(filename);
    if (!file.good()) {
        cerr << "Error: cannot open file " << filename << endl;
        exit(1);
    }
    string line;
    while (getline(file, line)) {
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        spilt_string(line, words);
    }
    file.close();
    return words.size();
}

/**
 * @brief record all grams in the `words` vector and store them in the vector `grams` by the appearance order.
 * Later we will use the `grams` vector to construct the co-occurrence matrix.
 * e.g. :
 *  if we have a sentence like: `I like to eat apple`
 *  and our n is 2, then we can form the gram `I like` and `like to` and etc.
 * 
 * words = ["I", "like", "to", "eat", "apple"]
 * grams = ["I like", "like to", "to eat", "eat apple"]         // n equals 2
 * grams = ["I like to", "like to eat", "to eat apple"]         // n equals 3
 * 
 * @param words     vector of words
 * @param grams     vector to store the grams
 * @param n         hyperparameter `n`
 * @return size_t   the size of the `grams` vector
 */
size_t record_grams(const vector<string>& words, vector<string>& grams, int n) {
    // TODO: implement this function
    /* Your code here */
    for (int i = 0, j = i+n; j <= words.size(); i++, j++) {
        string gram = "";
        for (int k = i; k < j-1; k++) {
            gram += words[k] + " ";
        }
        gram += words[j-1];
        grams.emplace_back(gram);
    }
    return grams.size();
}

/**
 * @brief Use `words` vector to construct a word index map. 
 * The key is the word and the value is the position of the word in the alphabetical order.
 * e.g. :
 * words: ["I", "like", "to", "eat", "apple"]
 * word_index: {"I": 0, "apple": 1, "eat": 2, "like": 3, "to": 4}
 * 
 * @param words         vector of words
 * @param word_index    map to store the word index
 * @return size_t       the size of the `word_index` map
 */
size_t set_word_index(const vector<string>& words, map<string, int>& word_index) {
    // TODO: implement this function
    /* Your code here */
    auto tmpset = set<string>(words.begin(), words.end());
    auto dup_words = vector<string>(tmpset.begin(), tmpset.end());
    for (int i = 0; i < dup_words.size(); i++) {
        word_index[dup_words[i]] = i;
    }
    return word_index.size();
}

/**
 * @brief Set up the coocur matrix object. 
 * Notice that you may need more data structure to implement this functions.
 * Thus, you are free to modify the signature of this function and I strongly suggest you to do so.
 * If you need to define a new data structure to store the data, you should define it as a global variable in the `grams.cpp` file.
 * 
 * @param grams             vector of grams
 * @param word_index        map of word index
 * @param coocur_matrix     vector of vector to store the co-occurrence matrix
 */
void set_coocur_matrix(const vector<string>& grams, const map<string, int>& word_index, vector<vector<int>>& coocur_matrix) {
    // TODO: impelement this function. Store the co-occurrence matrix in the `coocur_matrix` vector.
    /* Your code here */
    coocur_matrix = vector<vector<int>>(grams.size(), vector<int>(grams.size(), 0));
    for (auto gram : grams) {
        vector<string> tmp;
        spilt_string(gram, tmp);
        int n = tmp.size();
        int center = (n + 1) / 2;                        // the center of the gram, which is the word we want to count.(I call it key here.)
        int key_index = word_index.at(tmp[center]);      // the index of the key word in the co-ocurrence matrix
        for (int i = 0; i < n; i++) {
            if (i == center) continue;
            int index = word_index.at(tmp[i]);
            coocur_matrix[key_index][index]++;
        }
    }
    return;
}

/**
 * @brief normalize the co-occurrence matrix by row.
 * e.g.:
 * co-occurrence matrix:
 *  [[1,0,3,1], [0,1,1,0], [2,1,0,0], [0,0,0,1]]
 * normalized matrix:
 *  [[0.2, 0, 0.6, 0.2], [0, 0.5, 0.5, 0], [2/3, 1/3, 0, 0], [0, 0, 0, 1]]
 * 
 * @param coocur_matrix         co-occurrence martix
 * @param normalized_matrix     normalized co-occurrence martix
 */
void normalize_matrix(const vector<vector<int>>& coocur_matrix, vector<vector<double>>& normalized_matrix) {
    // TODO: implement this function
    /* Your code here */
    normalized_matrix = vector<vector<double>>(coocur_matrix.size(), vector<double>(coocur_matrix[0].size(), 0.0));
    for (int i = 0; i < coocur_matrix.size(); i++) {
        double row_sum = accumulate(coocur_matrix[i].begin(), coocur_matrix[i].end(), 0.0);
        for (int j = 0; j < coocur_matrix[0].size(); j++) {
            normalized_matrix[i][j] = (double)coocur_matrix[i][j] / row_sum;
        }
    }
}

/**
 * @brief save the normalized co-occurrence matrix to a file. The first line should be the words which each row represents.
 * each number is separated by a space.
 * e.g.:
 * a b c d
 * 0.2 0 0.6 0.2
 * 0 0.5 0.5 0
 * 0.6666666666666666 0.3333333333333333 0 0
 * 0 0 0 1
 * 
 * @param filename      file name of the output file
 * @param matrix        normalized co-occurrence martix
 * @param word_index    map of word to index
 */
void save_matrix(const string& filename, const vector<vector<double>>& matrix, const map<string, int>& word_index) {
    // TODO: save the normalized_matrix to file `result.txt`. Notice that the first row should be the words.
    /* Your code here */
    ofstream file(filename);
    if (!file.good()) {
        cout << "Error: cannot open file " << filename << endl;
        return;
    }
    for (auto it = word_index.begin(); it != word_index.end(); it++) {
        file << it->first << " ";
    }
    file << endl;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            file << matrix[i][j] << " ";
        }
        file << endl;
    }
    file.close();
}

/**
 * @brief restore the normalized co-occurrence matrix from file `filename`.
 * Assume that the file is in the same format as the one in `save_matrix` function.
 * e.g.:
 * 0.2 0 0.6 0.2
 * 0 0.5 0.5 0
 * 0.6666666666666666 0.3333333333333333 0 0
 * 0 0 0 1
 * 
 * @param filename    file name of the input file
 * @param matrix      normalized co-occurrence martix
 * @param index_word  map of index to word
 */
void restore_matrix(const string& filename, vector<vector<double>>& matrix, map<int, string>& index_word) {
    // hint: you can refer to the `set_word_index` function and `split_string` function.
    // TODO: restore the normalized_matrix from file `result.txt`.
    /* Your code here */
    // TODO: clean this function.
    ifstream file(filename);
    if (!file.good()) {
        cerr << "Error: cannot open file " << filename << endl;
        exit(1);
    }
    string line;
    regex _regex("\\s");
    getline(file, line);
    sregex_token_iterator regex_iter(line.begin(), line.end(), _regex, -1);
    sregex_token_iterator end;
    int index = 0;
    while (regex_iter != end) {
        index_word[index++] = *regex_iter;
        ++regex_iter;
    }
    while (getline(file, line)) {
        vector<double> row;
        sregex_token_iterator regex_iter(line.begin(), line.end(), _regex, -1);
        sregex_token_iterator end;
        while (regex_iter != end) {
            row.emplace_back(stod(*regex_iter));
            ++regex_iter;
        }
        matrix.emplace_back(row);
    }
    file.close();
    return;
}

/**
 * @brief find the 5 most similar words to the given word. If there are less than 5 words, then simply return all of them.
 * You should sort them by the similarity score in descending order.
 * If they have the same similarity score, then sort them by the alphabetical order.
 * The similarity of two words can be evaluated by Euclidean Metric.
 * e.g.:
 * apple:   0.1 0.2 0.5 0.2
 * orange:  0.2 0.1 0.3 0.4
 * then the similarity of them can be calculated by:
 * sqrt((0.1-0.2)^2 + (0.2-0.1)^2 + (0.5-0.3)^2 + (0.2-0.4)^2)
 * 
 * @param word                  given word
 * @param matrix                normalized co-occurrence martix
 * @param index_word            map of index to word
 * @return vector<string>       vector of 5 most similar words
 */
vector<string> most_similar(const string& word, const vector<vector<double>>& matrix, const map<int, string>& index_word) {
    // TODO: implement this function. 
    /* Your code here */
    vector<pair<int, double>> similarities;
    auto iter = find_if(index_word.begin(), index_word.end(), [&](const pair<int, string>& p) {
        return p.second == word;
    });
    if (iter == index_word.end()) {
        cerr << "Error: cannot find word " << word << endl;
        return vector<string>();
    }
    int index = iter->first;
    for (int i = 0; i < matrix.size(); i++) {
        double sum = 0.0;
        for (int j = 0; j < matrix[0].size(); j++) {
            sum += pow(matrix[i][j] - matrix[index][j], 2);
        }
        similarities.emplace_back(make_pair(i, sqrt(sum)));
    }
    sort(similarities.begin(), similarities.end(), [&](pair<int, double> x, pair<int, double> y) {
        return (x.second > y.second) || (x.second == y.second && x.first < y.first);
    });
    vector<string> res;
    for (int i = 0; i < similarities.size() && i < 5; i++) {
        res.emplace_back(index_word.at(similarities[i].first));
    }
    return res;
}