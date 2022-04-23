#ifndef __AUDIO_H
#define __AUDIO_H

#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <pthread.h>

using namespace std;

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
    atomic_bool _loop;
    int _volume;
    pid_t _loop_pid = 0;
};

#endif// !AUDIO_H