# Tetris Clone

This is a Tetris clone built in C++ using raylib. It includes many traditional Tetris features such as:
- Super Rotation System (360 rotation and wall kicks)
- Block soft dropping
- 

![example image](example.png)

## Dependencies
- Git
- CMake
- C++ 17 or above
- OpenGL Development Libraries (Included in Windows and macOS)
- Homebrew (macOS)

### Use the below commands in the terminal or download from official websites to install the dependencies if you don't already have them.

### Windows
Download and install [git](https://git-scm.com/downloads/win), [CMake](https://cmake.org/download/), and a C++ compiler like [MinGW](https://www.msys2.org/).<br>

<b>You may need to add git, CMake, and your compiler to your ``PATH`` if it wasn't done during installation.<b><br>

#### Linux (Adjust for non Ubuntu-based platforms)

```
sudo apt update
sudo apt install git
sudo apt install cmake
sudo apt install libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev
```

### macOS
If you don't already have Homebrew: ```/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"```<br>

```
brew update
brew install git
brew install cmake
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

Run CMake.<br>
```cmake ..```

Build the executable.<br>
```make```

### If you followed the steps correctly, the game executable `TetrisClone.exe` should be in your build directory.