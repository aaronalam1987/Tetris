#include "audio.h"

extern Audio audio;

Audio::Audio()
{
    soundMap = {
        {1, &rotateSound},
        {2, &dropSound},
        {3, &clearSound},
        {4, &startSound},
        {5, &gameOverSound}

    };
}

void Audio::loadAudio()
{
    // Load all buffers at the start.
    rotateBuffer.loadFromFile("assets/audio/pieceRotate.wav");
    dropBuffer.loadFromFile("assets/audio/dropPiece.wav");
    clearBuffer.loadFromFile("assets/audio/clearLine.wav");
    startBuffer.loadFromFile("assets/audio/startGame.wav");
    gameOverBuffer.loadFromFile("assets/audio/gameOver.ogg");

    // Load all buffers into sound.
    rotateSound.setBuffer(rotateBuffer);
    dropSound.setBuffer(dropBuffer);
    clearSound.setBuffer(clearBuffer);
    startSound.setBuffer(startBuffer);
    gameOverSound.setBuffer(gameOverBuffer);
}

void Audio::playBGM()
{
    BGM.openFromFile("assets/audio/BGM.ogg");
    BGM.setVolume(60);
    BGM.setLoop(true);
    BGM.play();
}

void Audio::stopBGM()
{
    BGM.stop();
}

void Audio::playSound(int sound)
{
    if (soundMap.find(sound) != soundMap.end())
    {
        soundMap[sound]->play();
    }
}
