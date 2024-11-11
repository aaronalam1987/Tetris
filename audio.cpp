#include "audio.h"

sf::SoundBuffer buffer;
sf::SoundBuffer buffer2;
sf::Sound pieceRotate;
sf::Sound dropPiece;
sf::Sound clearLine;
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
            pieceRotate.setBuffer(buffer);
            pieceRotate.play();
        break;

        case 2:
            buffer.loadFromFile("assets/audio/dropPiece.wav");
            dropPiece.setBuffer(buffer);  
            dropPiece.play();
        break;

        case 3:
            buffer2.loadFromFile("assets/audio/clearLine.wav");
            clearLine.setBuffer(buffer2);  
            clearLine.play();
        break;
    }
    
}