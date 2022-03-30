#include "grams.h"
#include "util.h"
#include <iostream>
#include <regex>
#include <set>
#include <numeric>

using namespace std;

// define some global variables
vector<string> words;                       // all words, sort by appearance order
vector<pair<string, int>> freq;             // frequency of coocurrence of each word
// for simplicity, each row of the co-occurrence matrix represents the word by lexicographical order
// thus, we'd use a map to store the index of the word which is `word_index`
map<string, int> word_index;                // mapping the word to the index in the co-occurrence matrix
map<int, string> index_word;                // mapping the index to the word in the co-occurrence matrix
vector<vector<int>> coocur_matrix;          // co-ocurrence martix, each row is a n-gram
vector<vector<double>> normalized_matrix;   // normalized co-ocurrence martix
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
 * @brief go through the vector `words` and record the frequency of each word.
 * e.g.:
 *  words = ["a", "a", "b", "c", "d", "e", "e"]
 *  freq = [("a", 2), ("b", 1), ("c", 1), ("d", 1), ("e", 2)]
 * 
 * @param words     vector of words
 * @param freq      vector to store the frequency of each word
 * @return size_t   the size of the `freq` vector
 */
size_t record_freq(const vector<string>& words, vector<pair<string, int>>& freq) {
    // hint: you may find the `map` data structure useful
    // TODO: impelement this function.
    /* Your code here */
    map<string, int> word_freq;
    for (auto word : words) {
        if (word_freq.find(word) == word_freq.end()) {
            word_freq[word] = 1;
        } else {
            word_freq[word]++;
        }
    }
    for (auto word_freq_pair : word_freq) {
        freq.push_back(word_freq_pair);
    }
    return freq.size();
}

/**
 * @brief Filter out the 3000 most frequent words.
 * !!Notice that if a word is not in the 3000 most frequent words, it should be replaced by `<unk>`.
 * 
 * @param freq      vector of words and their frequency
 * @param words     original vector of words. You should change the vector `words` to keep the 3000 most frequent words.
 */
void filter_words(vector<pair<string, int>>& freq, vector<string>& words) {
    // hint: you can use function `sort` to sort the vector `freq` by modify the compare function.
    // if you want to write a compare function more gracefully, you can try to use `lambda expression`(It's a new feature in C++11.).
    // TODO: implement this function.
    /* Your code here */
    sort(freq.begin(), freq.end(), [](pair<string, int>& a, pair<string, int>& b) {
        return (a.second > b.second) || (a.second == b.second && a.first < b.first);
    });
    set<string> word_set;
    for (size_t i = 0; i < freq.size() && i < 3000; i++) {
        word_set.insert(freq[i].first);
    }
    for (size_t i = 0; i < words.size(); i++) {
        if (word_set.find(words[i]) == word_set.end()) {
            words[i] = "<unk>";
        }
    }
    return;
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
    for (size_t i = 0; i < dup_words.size(); i++) {
        word_index[dup_words[i]] = i;
    }
    return word_index.size();
}

/**
 * @brief Set up the coocur matrix object. 
 * Each row of the coocur matrix represents the word by lexicographical order. 
 * The value of each element in the co-occurrence matrix is the number of times that two words appear together.
 * e.g. :
 * consider n as 3,
 * words: ["<unk>", "I", "like", "to", "eat", "apple", "<unk>"]
 * coocur_matrix:   (sorted by lexicographical order. Thus, these rows represent the words ["<unk>", "I", "apple", "eat", "like", "to"])
 * coocur_matrix[1][4] == 1 represents that if consider "I" as center word, the number of times that "I" and "like" appear together is 1.
 * [0, 1, 1, 0, 0, 0]
 * [1, 0, 0, 0, 1, 0]
 * [1, 0, 0, 1, 0, 0]
 * [0, 0, 1, 0, 0, 1]
 * [0, 1, 0, 0, 0, 1]
 * [0, 0, 0, 1, 1, 0]
 * 
 * @param words             vector of words
 * @param word_index        map of word index
 * @param coocur_matrix     vector of vector to store the co-occurrence matrix
 * @param n                 hyper-parameter of n-gram
 */
void set_coocur_matrix(const vector<string>& words, const map<string, int>& word_index, vector<vector<int>>& coocur_matrix, int n) {
    // TODO: impelement this function. Store the co-occurrence matrix in the `coocur_matrix` vector.
    /* Your code here */
    int size = words.size();
    coocur_matrix = vector<vector<int>>(word_index.size(), vector<int>(word_index.size(), 0));
    for (int left = 0, right = n, center = (n + 1) / 2 - 1; right <= size; left++, right++, center++) {
        cout << (double)center/size << '\r';
        for(int i = left; i < right; i++) {
            if (i == center) {
                continue;
            }
            int i_index = word_index.at(words[i]);
            int center_index = word_index.at(words[center]);
            coocur_matrix[center_index][i_index]++;
        }
    }
    return;
}

/**
 * @brief normalize the co-occurrence matrix by column.
 * e.g.:
 * co-occurrence matrix:
 * [0, 2, 1, 0, 0, 0]
 * [2, 0, 0, 0, 1, 0]
 * [1, 0, 0, 1, 0, 0]
 * [0, 0, 1, 0, 0, 1]
 * [0, 1, 0, 0, 0, 1]
 * [0, 0, 0, 1, 1, 0]
 * normalized matrix:
 * [0, 2/3, 0.5, 0, 0, 0]
 * [2/3, 0, 0, 0, 0.5, 0]
 * [1/3, 0, 0, 0.5, 0, 0]
 * [0, 0, 0.5, 0, 0, 0.5]
 * [0, 1/3, 0, 0, 0, 0.5]
 * [0, 0, 0, 0.5, 0.5, 0]
 * 
 * @param coocur_matrix         co-occurrence martix
 * @param normalized_matrix     normalized co-occurrence martix
 */
void normalize_matrix(const vector<vector<int>>& coocur_matrix, vector<vector<double>>& normalized_matrix) {
    // TODO: implement this function
    /* Your code here */
    vector<double> col_sum = vector<double>(coocur_matrix[0].size(), 0.0);
    normalized_matrix = vector<vector<double>>(coocur_matrix.size(), vector<double>(coocur_matrix[0].size(), 0.0));
    for (size_t i = 0; i < coocur_matrix.size(); i++) {
        for (size_t j = 0; j < coocur_matrix[0].size(); j++) {
            col_sum[j] += coocur_matrix[i][j];
        }
    }
    for (size_t i = 0; i < coocur_matrix.size(); i++) {
        for (size_t j = 0; j < coocur_matrix[0].size(); j++) {
            normalized_matrix[i][j] = (double)coocur_matrix[i][j] / col_sum[j];
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
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[0].size(); j++) {
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
 * @brief calculate the cosine similarity of word i and word j
 * you can calculate the cosine similarity by using the formula:
 * cosine_similarity = sum(matrix[i][k]*matrix[j][k]) / (sqrt(sum(matrix[i][k]^2)) * sqrt(sum(matrix[j][k]^2)))
 * if you can not understand the formula, please refer to the lab notes.
 * 
 * @param matrix    normalized co-occurrence martix
 * @param i         index of word i
 * @param j         index of word j
 * @return double   cosine similarity of word i and word j
 */
double similarity(const vector<vector<double>>& matrix, size_t i, size_t j) {
    // TODO: implement this function
    /* Your code here */
    double sum = 0.0;
    double i_norm = 0.0, j_norm = 0.0;
    for (size_t k = 0; k < matrix[0].size(); k++) {
        sum += matrix[i][k] * matrix[j][k];
        i_norm += matrix[i][k] * matrix[i][k];
        j_norm += matrix[j][k] * matrix[j][k];
    }
    double res = sum / (sqrt(i_norm) * sqrt(j_norm));
    return res == 0 ? 0 : res;
}

/**
 * @brief find the 5 most similar words to the given word. If there are less than 5 words, then simply return all of them.
 * You should sort them by the similarity score in descending order.
 * If they have the same similarity score, then sort them by the alphabetical order.
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
    for (size_t i = 0; i < matrix.size(); i++) {
        // if ((int)i == index) continue;
        double res = similarity(matrix, index, i);
        similarities.emplace_back(make_pair(i, res));
    }
    sort(similarities.begin(), similarities.end(), [](pair<int, double>& x, pair<int, double>& y) {
        return (x.second > y.second) || (x.second == y.second && x.first < y.first);
    });
    vector<string> res;
    for (size_t i = 0; i < similarities.size() && i < 5; i++) {
        res.emplace_back(index_word.at(similarities[i].first));
    }
    return res;
}