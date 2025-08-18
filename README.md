# Tetris Clone

This is a Tetris clone built in C++ using raylib. It includes most traditional Tetris features such as the Super Rotation System, speed increases, rotations, and more!

![example image](example.png)

## Dependencies
- Git
- CMake
- C++ 17 or above
- OpenGL Development Libraries

### Use the below commands in the terminal if you don't have the dependencies.
```
sudo apt update
sudo apt install git
sudo apt install cmake
sudo apt install libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev
```

## Installation
Download or clone the repository into your directory of choice.<br>
```git clone https://github.com/rajahw/TetrisClone.git```

Create a build directory inside the project directory `TetrisClone`.<br>
```
cd tetrisclone
mkdir build
cd build
```

### Adjust the CMake and build command flags if needed.

Run CMake.<br>
```cmake ..```

Build the executable.<br>
```make```

### If you followed the steps correctly, the game executable `TetrisClone.exe` should be in your build directory.