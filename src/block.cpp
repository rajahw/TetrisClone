#include "include/block.h"

Block::Block() {}

void Block::moveLeft() {
    if (!atLeft()) {
        position.x -= size;
        centerX--;
    }
}

void Block::moveRight() {
    if (!atRight()) {
        position.x += size;
        centerX++;
    }
}

void Block::moveDown() {
    if (!atBottom()) {
        position.y += size;
        centerY++;
    }
}

void Block::draw() {
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < dimensions; j++) {
            if (body[rotation][j][i] == '#') {
                DrawRectangle(position.x + i * size + 1, position.y + j * size + 1, size - 1, size - 1, color);
            }
        }
    }
}

void Block::rotateCounter() {
    rotation = rotation > 0 ? rotation - 1 : 3;
}

void Block::rotateClockwise() {
    rotation = rotation < 3 ? rotation + 1 : 0;
}

bool Block::collidingLeft(const Arena& arena) {
    if (!atLeft()) {
        for (int row = 0; row < dimensions; row++) {
            for (int col = 0; col < dimensions; col++) {
                if (body[rotation][row][col] == '#') {
                    if (arena.body[centerY + row][centerX + col - 1] != 'X') {
                        return true;
                    }
                }
            }
        }
        return false;
    } else {
        return false;
    }
}

bool Block::collidingRight(const Arena& arena) {
    if (!atRight()) {
        for (int row = 0; row < dimensions; row++) {
            for (int col = 0; col < dimensions; col++) {
                if (body[rotation][row][col] == '#') {
                    if (arena.body[centerY + row][centerX + col + 1] != 'X') {
                        return true;
                    }
                }
            }
        }
        return false;
    } else {
        return false;
    }
}

bool Block::collidingBottom(const Arena& arena) {
    if (!atBottom()) {
        for (int row = 0; row < dimensions; row++) {
            for (int col = 0; col < dimensions; col++) {
                if (body[rotation][row][col] == '#') {
                    if (arena.body[centerY + row + 1][centerX + col] != 'X') {
                        return true;
                    }
                }
            }
        }
        return false;
    } else {
        return false;
    }
}

bool Block::rotationIsPossible(const Arena& arena, const Offset& offset) {
    int newX, newY;

    for (int row = 0; row < dimensions; row++) {
        for (int col = 0; col < dimensions; col++) {
            newX = centerX + offset.x + col;
            newY = centerY + offset.y + row;
            if (body[rotation][row][col] == '#') {
                if (newX < 0 || newX >= columns || newY < 0 || newY >= rows) {
                    return false;
                } else if (arena.body[newY][newX] != 'X') {
                    return false;
                }
            }
        }
    }
    return true;
}

void Block::counterKick(const Arena& arena) {
    rotateCounter();
    for (int test = 0; test < 5; test++) {
        if (rotationIsPossible(arena, counterOffset[rotation][test])) {
            centerX += counterOffset[rotation][test].x;
            centerY += counterOffset[rotation][test].y;
            position.x += counterOffset[rotation][test].x * size;
            position.y += counterOffset[rotation][test].y * size;
            return;
        }
    }
    rotateClockwise();
}

void Block::clockwiseKick(const Arena& arena) {
    rotateClockwise();
    for (int test = 0; test < 5; test++) {
        if (rotationIsPossible(arena, clockwiseOffset[rotation][test])) {
            centerX += clockwiseOffset[rotation][test].x;
            centerY += clockwiseOffset[rotation][test].y;
            position.x += clockwiseOffset[rotation][test].x * size;
            position.y += clockwiseOffset[rotation][test].y * size;
            return;
        }
    }
    rotateCounter();
}