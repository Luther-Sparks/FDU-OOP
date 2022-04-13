#include "grams.h"
#include "util.h"
#include <iostream>
#include <regex>
#include <set>
#include <numeric>
#include <iomanip>
#include <cmath>

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
        split_string(line, words);
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
    int size = words.size();
    coocur_matrix = vector<vector<int>>(word_index.size(), vector<int>(word_index.size(), 0));
    for (int left = 0, right = n, center = (n + 1) / 2; right <= size; left++, right++, center++) {
        if (center % 100 == 0) {
            cout << setprecision(5) << (double)center/size << '\r';     // This is to show the progress of building the co-occurrence matrix.
        }
        // If you want, you can do the similar thing to print the progress of other parts.
        // TODO: impelement this function. Store the co-occurrence matrix in the `coocur_matrix` vector.
        /* Your code here */
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
    double res;
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
    cerr << "Error: cannot find word " << word << endl;
    return vector<string>();
}