#include <iostream>
#include <cstring>
#include "util.h"
#include "grams.h"

using namespace std;

/**
 * @brief train the model.
 * 
 * @param n             hyperparameter `n`
 * @param filename      file name of the dataset file
 */
void train(const int& n, const string& filename) {
    record_words(filename, words);          // record all words
    cout << "done with record_words" << endl;
    // padding the words vector with word `<unk>`
    for (auto i = 0; i < n - 1; i++) {
        words.insert(words.begin(), "<unk>");
        words.insert(words.end(), "<unk>");
    }
    record_freq(words, freq);                               // record the frequency of each word
    cout << "done with record_freq" << endl;
    filter_words(freq, words);                              // filter the less frequent words by replacing them by `<unk>`
    cout << "done with filter_words" << endl;
    set_word_index(words, word_index);                      // store the index of the word in the matrix
    cout << "done with set_word_index" << endl;
    set_coocur_matrix(words, word_index, coocur_matrix, n); // store the co-occurrence matrix
    cout << "done with set_coocur_matrix" << endl;
    normalize_matrix(coocur_matrix, normalized_matrix);     // normalize the matrix

    // Now we have the 	normalized co-occurrence matrix, we can use it to do some cool stuff.
    // We want to save the normalized matrix to a file, so that we can use it later.
    save_matrix("matrix.txt", normalized_matrix, word_index);
    return;
}

void test(const string& testfile, const string& matrix_file) {
    restore_matrix(matrix_file, normalized_matrix, index_word);
    // Now you should try to use the normalized matrix to find the most similar words.
    // We believe that the more similar the words are, the more likely they have the same context.
    // In this case, you can use this method to find the most similar words.
    ifstream file(testfile);                             // open the test file
    if (!file.good()) {
        cerr << "Error: cannot open file " << testfile << endl;
        exit(1);
    }
    string word;
    // first, we read the words from the test file. Each row of the test file is a word.
    vector<string> test_words;
    while (getline(file, word)) {
        test_words.emplace_back(word);
    }
    file.close();
    // Now, we shall find the 5 most similar words for each word in the test file.
    ofstream outfile("output.txt");
    if (!outfile.good()) {
        cerr << "Error: cannot open file output.txt" << endl;
        exit(1);
    }
    for (auto w : test_words) {
        auto vec = most_similar(w, normalized_matrix, index_word);
        for (auto item : vec) {
            outfile << item << " ";
        }
        outfile << endl;
    }
    outfile.close();
    
    return;
}

int main(int argc, const char** argv) {
    if (strcmp(argv[1], "--train") != 0 && strcmp(argv[1], "--test") != 0) {
        cout << "Invalid input" << endl;
        cout << "Usage: ./n_gram --train <n> <input file>" << endl;
        cout << "       ./n_gram --test <test file> <matrix file>" << endl;
        return 1;
    }
    if (strcmp(argv[1], "--train") == 0) {
        if (argc != 4) {
            cout << "Invalid input" << endl;
            cout << "Usage: .n_/gram --train <n> <input file>" << endl;
            return 1;
        }
        int n = stoi(argv[2]);                  // hyperparameter `n`
        string filename = argv[3];              // the input file name
        train(n, filename);
    }
    else {
        if (argc != 4) {
            cout << "Invalid input" << endl;
            cout << "Usage: ./n_gram --test <test file> <matrix file>" << endl;
            return 1;
        }
        string test_file = argv[2];
        string matrix_file = argv[3];
        test(test_file, matrix_file);
    }
    string str;
    return 0;
}