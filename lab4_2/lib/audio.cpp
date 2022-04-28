
#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>

#ifndef __SRC_FILE
#define __SRC_FILE
#endif // !__SRC_FILE
#include "audio.h"

using std::cin;

Audio::~Audio() {
    this->stop();
    if (_t != nullptr) {
        _t->join();
        delete _t;
        _t = nullptr;
    }
}

void Audio::play_once() {
    _t = new thread([this]() {
        auto tmp = "play " + _file_name;
        auto command = tmp.c_str();
        if (mciSendString(command, NULL, 0, NULL) != 0) {
            cout << "Error playing sound file: " << command << endl;
        }
        tmp = "setaudio " + _file_name + " volume to " + std::to_string(_volume*10);
        command = tmp.c_str();
        if (mciSendString(command, NULL, 0, NULL) != 0) {
            cout << "Error setting volume: " << command << endl;
        }
    });
}

void Audio::play_loop() {
    _loop = true;
    _t = new thread([this]() {
        auto tmp = "play " + _file_name + " repeat";
        auto command = tmp.c_str();
        if (mciSendString(command, NULL, 0, NULL) != 0) {
            cout << "Error playing sound file: " << command << endl;
        }
        tmp = "setaudio " + _file_name + " volume to " + std::to_string(_volume*10);
        command = tmp.c_str();
        if (mciSendString(command, NULL, 0, NULL) != 0) {
            cout << "Error setting volume: " << command << endl;
        }
    });
}

void Audio::stop() {
    _loop = false;
    auto tmp = "stop " + _file_name;
    auto command = tmp.c_str();
    if (mciSendString(command, NULL, 0, NULL) != 0) {
        cout << "Error playing sound file: " << command << endl;
    }
    _t->join();
    delete _t;
    _t = nullptr;
}

#else
#include "audio.h"
#include <signal.h>
#include <unistd.h>
using std::to_string;

Audio::~Audio() {
    if (_t != nullptr) {
        delete _t;
        _t = nullptr;
    }
}

void Audio::play_once() {
    _t = new thread([&, this](){
        this->_loop_pid = fork();
        if (this->_loop_pid == 0) {
            execlp("afplay", "afplay", "-v", std::to_string(_volume).c_str(), _file_name.c_str(), NULL);
        }
        else {
            waitpid(this->_loop_pid, NULL, 0);
        }
    });
}

void Audio::play_loop() {
    _loop = true;
    _t = new thread([&, this]() {
        while (_loop) {
            this->_loop_pid = fork();
            if (this->_loop_pid == 0) {
                execlp("afplay", "afplay", "-v", std::to_string(_volume).c_str(), _file_name.c_str(), NULL);     
                }
            else {
                waitpid(this->_loop_pid, NULL, 0);
            }
        }
    });
}

void Audio::stop() {
    if (_loop_pid != 0) {
        _loop = false;
        int status = kill(this->_loop_pid, 0);
        if (status != -1) {
            kill(this->_loop_pid, SIGKILL);
        }
        _t->join();
        delete _t;
        _t = nullptr;
        _loop_pid = 0;
    }
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