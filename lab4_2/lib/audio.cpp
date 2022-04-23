#include "audio.h"
#ifdef _WIN32
// FIXME
#else
#include <signal.h>
#include <unistd.h>

struct member {
    int volume;
    const char* file_name;
};

Audio::~Audio() {
    if (_t != nullptr) {
        _t->join();
        delete _t;
    }
}

void* temp(void* args) {
    member* m = (member*)args;
    if (m != NULL) {
        string cmd = "afplay -v " + to_string(m->volume) + " " + m->file_name;
        system(cmd.c_str());
    }
    return nullptr;
}


void Audio::play_once() {
    _t = new thread([&, this](){
        this->_loop_pid = fork();
        if (this->_loop_pid == 0) {
            execlp("afplay", "afplay", "-v", to_string(_volume).c_str(), _file_name.c_str(), NULL);
        }
        else {
            waitpid(this->_loop_pid, NULL, 0);
        }
    });
    _t->join();
    delete _t;
    _t = nullptr;
}

void Audio::play_loop() {
    _loop = true;
    _t = new thread([&, this]() {
        while (_loop) {
            this->_loop_pid = fork();
            if (this->_loop_pid == 0) {
                execlp("afplay", "afplay", "-v", to_string(_volume).c_str(), _file_name.c_str(), NULL);     
                }
            else {
                waitpid(this->_loop_pid, NULL, 0);
            }
        }
    });
}

void Audio::stop() {
    _loop = false;
    kill(this->_loop_pid, SIGKILL);
    _t->join();
    delete _t;
    _t = nullptr;
}

#endif

bool Audio::get_loop() {
    return _loop;
}

void Audio::set_loop(bool loop) {
    this->_loop = loop;
}

int Audio::get_volume() {
    return _volume;
}

void Audio::set_volume(int volume) {
    this->_volume = volume;
}