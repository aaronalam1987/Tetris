#ifndef AUDIO_H
#define AUDIO_H
#include <SFML/Audio.hpp>

class Audio{
    public:
        void loadAudio();
        void playBGM();
        void playSound(int sound);
};

#endif