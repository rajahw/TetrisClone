cmake_minimum_required(VERSION 3.0.0)
project(TetrisClone CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS OFF)
set(RAYLIB_STATIC TRUE)

find_package(raylib CONFIG REQUIRED)

add_executable(app
    main.cpp
    arena.cpp
    block.cpp
    game.cpp
    tetros.cpp
)

target_link_libraries(app PRIVATE raylib)