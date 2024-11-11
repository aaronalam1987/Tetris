#include "audio.h"

sf::SoundBuffer buffer;
sf::SoundBuffer buffer2;
sf::Sound dropPiece;
sf::Sound soundEffect;
sf::Music BGM;

void Audio::loadAudio(){
    
}

void Audio::playBGM(){
    BGM.openFromFile("assets/audio/BGM.ogg");
    BGM.setVolume(60);
    BGM.setLoop(true);
    BGM.play();
}

void Audio::playSound(int sound){
    switch(sound){
        case 1:
            buffer.loadFromFile("assets/audio/pieceRotate.wav");
            soundEffect.setBuffer(buffer);
            soundEffect.play();
        break;

        case 2:
            buffer.loadFromFile("assets/audio/dropPiece.wav");
            dropPiece.setBuffer(buffer);  
            dropPiece.play();
        break;

        case 3:
            buffer2.loadFromFile("assets/audio/clearLine.wav");
            soundEffect.setBuffer(buffer2);  
            soundEffect.play();
        break;

        case 4:
            buffer.loadFromFile("assets/audio/startGame.wav");
            soundEffect.setBuffer(buffer);  
            soundEffect.play();
        break;
    }
    
}