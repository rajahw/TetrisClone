#include "arena.h"

Arena::Arena() {
    initialize();
}

void Arena::initialize() {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            body[row][col] = 'X';
        }
    }
}

void Arena::draw() {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            if (body[row][col] == 'X') {
                DrawRectangle((col * size) + 1, (row * size) + 1, size - 1, size - 1, BLACK);
            } else if (body[row][col] == 'O') {
                DrawRectangle((col * size) + 1, (row * size) + 1, size - 1, size - 1, YELLOW);
            } else if (body[row][col] == 'I') {
                DrawRectangle((col * size) + 1, (row * size) + 1, size - 1, size - 1, SKYBLUE);
            } else if (body[row][col] == 'S') {
                DrawRectangle((col * size) + 1, (row * size) + 1, size - 1, size - 1, GREEN);
            } else if (body[row][col] == 'Z') {
                DrawRectangle((col * size) + 1, (row * size) + 1, size - 1, size - 1, RED);
            } else if (body[row][col] == 'L') {
                DrawRectangle((col * size) + 1, (row * size) + 1, size - 1, size - 1, ORANGE);
            } else if (body[row][col] == 'J') {
                DrawRectangle((col * size) + 1, (row * size) + 1, size - 1, size - 1, BLUE);
            } else if (body[row][col] == 'T') {
                DrawRectangle((col * size) + 1, (row * size) + 1, size - 1, size - 1, VIOLET);
            } else if (body[row][col] == 'G') {
                DrawRectangle((col * size) + 1, (row * size) + 1, size - 1, size - 1, LIGHTGRAY);
            }
        }
    }
}

void Arena::testPrint() {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            std::cout << body[row][col] << " ";
        }
        std::cout << "\n";
    }
}