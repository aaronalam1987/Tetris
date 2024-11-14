#include "audio.h"

sf::SoundBuffer rotateBuffer;
sf::SoundBuffer dropBuffer;
sf::SoundBuffer clearBuffer;
sf::SoundBuffer startBuffer;
sf::SoundBuffer gameOverBuffer;

sf::Sound rotateSound;
sf::Sound dropSound;
sf::Sound clearSound;
sf::Sound startSound;
sf::Sound gameOverSound;

sf::Music BGM;

void Audio::loadAudio()
{
    // Load all buffers at the start
    rotateBuffer.loadFromFile("assets/audio/pieceRotate.wav");
    dropBuffer.loadFromFile("assets/audio/dropPiece.wav");
    clearBuffer.loadFromFile("assets/audio/clearLine.wav");
    startBuffer.loadFromFile("assets/audio/startGame.wav");
    gameOverBuffer.loadFromFile("assets/audio/gameOver.ogg");
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
    switch (sound)
    {
    case 1:
        rotateSound.setBuffer(rotateBuffer);
        rotateSound.play();
        break;

    case 2:
        dropSound.setBuffer(dropBuffer);
        dropSound.play();
        break;

    case 3:
        clearSound.setBuffer(clearBuffer);
        clearSound.play();
        break;

    case 4:
        startSound.setBuffer(startBuffer);
        startSound.play();
        break;

    case 5:
        gameOverSound.setBuffer(gameOverBuffer);
        gameOverSound.play();
        break;
    }
}
