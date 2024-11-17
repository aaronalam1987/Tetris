# Tetris Clone

A Tetris clone created in C++ using the [SFML (Simple and Fast Multimedia Library)](https://www.sfml-dev.org/)  

This project is my recreation of the classic game, built as a personal challenge to learn more about game development and C++.

## Overview
Being one of the most iconic puzzle games of all time, Tetris needs no introduction.  

This project is my attempt to pay homage to the original whilst aiming to improve my skills in C++ and game development.  

The goal was to create a fully functional Tetris game with features that are true to the original.

## Dependencies
* [SFML 2.5.1](https://www.sfml-dev.org/download.php): A cross-platform multimedia library.

## Building the Project
To build this project, make sure you have the correct configuration setup for your preferred IDE (I used Visual Studio Code).  

You can simply run the provided Makefile and it will compile and output a main.exe file.

### Setting up Visual Studio Code  

Ensure you have the SFML include path included in your ```c_cpp_properties.json```:

```
"includePath": [  
"${workspaceFolder}/**",  
"C:\\SFML-2.5.1\\include"  
],
```
The MakeFile is configured to use statically linked SFML libraries so there is no need for additional SFML ```.dll``` files in ```main.exe``` directory. However, you will still need to include ```openal32.dll``` for audio support. This file is included in the SFML ```bin``` folder.   

## Assets
All game assets, including sprites and sound files are stored in the ```assets``` folder.  

You can modify these assets as long as you keep the original filenames.

## Features
I mean, is working a feature? It works as expected, blocks fall, make a line and clear them.  

* **Start Screen**: A simple "Start Game" screen before you jump into the action!  
* **Next Block Display**: Shows a preview of the next block, helping you to plan your moves.  
* **Dynamic Speed**: The game increases speed by 25ms for every line cleared after the first 10.
* **Sound Effects & Background Music**: Various sound effects for rotating, dropping and clearing lines along with upbeat retro-style background music.
* **Game Over Screen**: A game over screen displays with matching sound effects when you hit the top of the board!

## Planned Features
* **Highscore Feature**: Save and display the top ten highscores!
* **Pause Functionality**: Add the ability to pause the game.
* **Power-ups?**

## Controls
* **Space**: Rotate the current piece.
* **Down Arrow**: Increase the drop speed of the current piece.
* **Left/Right Arrows**: Move the piece left or right.
* **Escape**: Quit the game.

## Screenshots / Gameplay 
Here is a preview of the game:  

![image](https://github.com/user-attachments/assets/54da7745-2120-4792-bfc3-1a5c5052d4a8)
![image](https://github.com/user-attachments/assets/358a71df-cc73-406d-a1e2-1cf9643a01e2)
* **Video Preview**

[![Gameplay](https://img.youtube.com/vi/XRQx3CBUBZo/0.jpg)](https://www.youtube.com/watch?v=XRQx3CBUBZo)

## Credits
* **Background Music**: [NiKneT_Art on Pixabay](https://pixabay.com/users/niknet_art-46104493/?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=243998)
* **Font**: [Khurasan on dafont](https://www.dafont.com/khurasan.d5849)

## License  
This project is open-source and available under the MIT License.  

Feel free to fork, modify and contribute!
