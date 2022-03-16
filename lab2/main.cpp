#include <fstream>
#include <iostream>
#include <list>
#include <string>

#include "editor.h"
using namespace std;

// Code style (for anyone interested): {BasedOnStyle: Google, IndentWidth: 4,
// ColumnLimit: 120}

/**
 * @brief This is the main function of the editor.
 *        When execute the editor program, we can expect 0 or 1 argument(argc be
 * 1 or 2). If there is no argument, we will first ask user to input a filename.
 *        If there is one argument, we will open the file and start to edit.
 *        Otherwise, we will print the usage and exit.
 *        Usage: ./editor.exe [filename] (windows)
 *               ./editor [filename] (*nix)
 *        Please note that if the file do not exist, we will create it with specified filename.
 * @param argc
 * @param argv
 * @return int 0 if success, -1 if any unexpected error
 */
int main(int argc, char *argv[]) {
    string filename;
    if (argc <= 2) {
        if (argc == 1) {
            cout << "Please input a file name: ";
            getline(cin, filename);
        } else if (argc == 2) {
            filename = argv[1];
        }
        // Open the file or create a new file
        ifstream file(filename);
        if (!file.is_open()) {
            ofstream newfile(filename);
            if (!newfile.is_open()) {
                cout << "Error: Cannot create file " << filename << endl;
                return -1;
            }
            newfile.close();
            file.open(filename);
        }
        // Run the main loop
        main_loop(file, filename);
    } else {
// #ifdef __WIN32__
//         cerr << "Usage: ./editor.exe [filename]" << endl;
// #else
//         cerr << "Usage: ./editor [filename]" << endl;
// #endif
        return -1;
    }
    return 0;
}