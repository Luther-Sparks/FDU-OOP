#include <fstream>
#include <iostream>
#include <list>
#include <string>

using namespace std;

void read_lines(istream &is, list<string> &lines) {
    string line;
    while (getline(is, line)) {
        lines.push_back(line);
    }
}

void output_lines(ostream &os, const list<string> &lines, bool line_num = false) {
    int i = 1;
    for (const string &line : lines) {
        if (line_num) {
            os << i++ << ": ";
        }
        os << line << endl;
    }
}

void delete_line(list<string> &lines, int line_num) {
    auto it = lines.begin();
    advance(it, line_num - 1);
    lines.erase(it);
}

void insert_line(list<string> &lines, int line_num, const string &line) {
    auto it = lines.begin();
    advance(it, line_num - 1);
    lines.insert(it, line);
}

void replace_line(list<string> &lines, int line_num, const string &line) {
    auto it = lines.begin();
    advance(it, line_num - 1);
    *it = line;
}

void main_loop(istream &is, ostream &os) {
    list<string> lines;
    read_lines(is, lines);
    while (true){
        cout << "> ";
        string cmd;
        getline(cin, cmd);
        if(cmd == "q") {
            break;
        }else if(cmd == "l") {
            output_lines(os, lines, true);
        }else if(cmd.find('d') == 0) {
            int line_num = stoi(cmd.substr(2));
            delete_line(lines, line_num);
        }else if(cmd.find('i') == 0) {
            string str = cmd.substr(2);
            int line_num = stoi(str.substr(0, str.find(' ')));
            string line = str.substr(str.find(' ') + 1);
            insert_line(lines, line_num, line);
        }else if(cmd.find('r') == 0) {
            string str = cmd.substr(2);
            int line_num = stoi(str.substr(0, str.find(' ')));
            string line = str.substr(str.find(' ') + 1);
            replace_line(lines, line_num, line);
        }else { 
            cerr << "Invalid command" << endl;
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        main_loop(cin, cout);
    } else if (argc == 2) {
        ifstream ifs(argv[1]);
        if (ifs.is_open()) {
            main_loop(ifs, cout);
        } else {
            cout << "Could not open file " << argv[1] << endl;
        }
    } else {
        cout << "Too many arguments" << endl;
        return 1;
    }
}