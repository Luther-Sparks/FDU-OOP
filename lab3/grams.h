#ifndef GRAMS_H
#define GRAMS_H

#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

extern vector<string> words;                       // all words, sort by appearance order
extern vector<pair<string, int>> freq;             // frequency of occurrence of each word
extern map<string, int> word_index;                // mapping the word to its index in the co-occurrence matrix
extern vector<vector<int>> coocur_matrix;          // co-ocurrence martix, each row is a n-gram
extern vector<vector<double>> normalized_matrix;   // normalized co-ocurrence martix
extern map<int, string> index_word;                // mapping the index to the word in the co-occurrence matrix
// add your global variables here if you need.

size_t record_words(const string& filename, vector<string>& words);
size_t record_freq(const vector<string>& words, vector<pair<string, int>>& freq);
void filter_words(vector<pair<string, int>>& freq, vector<string>& words);
size_t set_word_index(const vector<string>& words, map<string, int>& word_index);
// you may want to modify the following functions signature if you need
void set_coocur_matrix(const vector<string>& words, const map<string, int>& word_index, vector<vector<int>>& coocur_matrix, int n);    // set up the co-occurrence matrix
void normalize_matrix(const vector<vector<int>>& coocur_matrix, vector<vector<double>>& normalized_matrix);
void save_matrix(const string& filename, const vector<vector<double>>& matrix, const map<string, int>& word_index);
void restore_matrix(const string& filename, vector<vector<double>>& matrix, map<int, string>& index_word);
double similarity(const vector<vector<double>>& matrix, size_t i, size_t j);
vector<string> most_similar(const string& word, const vector<vector<double>>& matrix, const map<int, string>& index_word);

#endif // !GRAMS_H