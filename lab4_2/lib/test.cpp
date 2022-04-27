#include "mingw.thread.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using mingw_stdthread::thread;

int foo() {
    thread t([](){
        while (true)
        {
            cout << "Hello, world!" << endl;
        }
    });
    t.join();
    return 0;
}

int main() {
    cout << "2" << endl;
    foo();
    return 0;
}