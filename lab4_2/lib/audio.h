#ifndef __AUDIO_H
#define __AUDIO_H

#include <iostream>
#include <string>
#include <atomic>
#include <pthread.h>
#ifdef _WIN32
#include "mingw.thread.h"
using mingw_stdthread::thread;
#else
#include <thread>
using std::thread;
using std::atomic_bool;
#endif


using std::string;
using std::cout;
using std::endl;

class Audio {
/**
 * @brief This class is used to play audio files.
 * 
 */
public:
    // initialize the audio object with the specified file name
    Audio(string file_name) :
         _file_name(file_name), _t(nullptr), _loop(false), _volume(20) {};
    // initialize the audio object with the specified file name and volume and decide whether to play the audio in loop
    Audio(string file_name, bool loop, int volume) :
         _file_name(file_name), _t(nullptr), _loop(loop), _volume(volume) {};
    // destructor
    ~Audio();
    // play the audio file for once
    void play_once();
    // play the audio file in loop
    void play_loop();
    // stop the audio file
    void stop();
    // set the volume of the audio file
    void set_volume(int volume);
    // get the volume of the audio file
    int get_volume();
    // get the status of the audio file
    bool get_loop();
    // set the status of the audio file
    void set_loop(bool loop);
private:
    string _file_name;
    thread* _t;
#ifndef _WIN32
    atomic_bool _loop;
#else
    bool _loop;
#endif // !_WIN32
    int _volume;
    pid_t _loop_pid = 0;
};

#endif// !AUDIO_H