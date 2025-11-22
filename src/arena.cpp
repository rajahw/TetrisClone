#include "include/arena.h"

Arena::Arena() {
    initialize();
}

void Arena::initialize() {
    for (int row = 0; row < rows; row++) {
        body[row].fill('X');
    }
}

void Arena::draw() {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            switch (body[row][col]) {
                case 'X':
                    DrawRectangle((col * size) + 1, (row * size) + 1, size - 1, size - 1, BLACK);
                break;
                case 'O':
                    DrawRectangle((col * size) + 1, (row * size) + 1, size - 1, size - 1, YELLOW);
                break;
                case 'I':
                    DrawRectangle((col * size) + 1, (row * size) + 1, size - 1, size - 1, SKYBLUE);
                break;
                case 'S':
                    DrawRectangle((col * size) + 1, (row * size) + 1, size - 1, size - 1, GREEN);
                break;
                case 'Z':
                    DrawRectangle((col * size) + 1, (row * size) + 1, size - 1, size - 1, RED);
                break;
                case 'L':
                    DrawRectangle((col * size) + 1, (row * size) + 1, size - 1, size - 1, ORANGE);
                break;
                case 'J':
                    DrawRectangle((col * size) + 1, (row * size) + 1, size - 1, size - 1, BLUE);
                break;
                case 'T':
                    DrawRectangle((col * size) + 1, (row * size) + 1, size - 1, size - 1, VIOLET);
                break;
                case 'G':
                    DrawRectangle((col * size) + 1, (row * size) + 1, size - 1, size - 1, LIGHTGRAY);
                break;
            }
        }
    }
}