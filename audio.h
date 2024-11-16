#ifndef AUDIO_H
#define AUDIO_H
#include <SFML/Audio.hpp>
#include <unordered_map>

class Audio
{
public:
    Audio();
    void loadAudio();
    void playBGM();
    void stopBGM();
    void playSound(int sound);

private:
    sf::SoundBuffer rotateBuffer, dropBuffer, clearBuffer, startBuffer, gameOverBuffer;
    sf::Sound rotateSound, dropSound, clearSound, startSound, gameOverSound;
    sf::Music BGM;
    std::unordered_map<int, sf::Sound *> soundMap;
};

#endif