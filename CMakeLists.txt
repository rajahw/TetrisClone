cmake_minimum_required(VERSION 3.15)

project(TetrisClone LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(game
    src/main.cpp
    src/arena.cpp 
    src/block.cpp 
    src/game.cpp 
    src/tetros.cpp
)

target_link_libraries(game ${CMAKE_SOURCE_DIR}/src/lib/libraylib.a)