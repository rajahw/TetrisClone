#include "include/block.h"

Block::Block() {}

void Block::moveLeft() {
    if (!atLeft()) {
        position.x -= size;
        arenaX--;
    }
}

void Block::moveRight() {
    if (!atRight()) {
        position.x += size;
        arenaX++;
    }
}
void Block::moveDown() {
    if (!atBottom()) {
        position.y += size;
        arenaY++;
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
    if (rotation > 0) {
        rotation--;
    } else {
        rotation = 3;
    }
}

void Block::rotateClockwise() {
    if (rotation < 3) {
        rotation++;
    } else {
        rotation = 0;
    }
}

bool Block::collidingLeft(const Arena& arena) {
    if (!atLeft()) {
        for (int row = 0; row < dimensions; row++) {
            for (int col = 0; col < dimensions; col++) {
                if (body[rotation][row][col] == '#') {
                    if (arena.body[arenaY + row][arenaX + col - 1] != 'X') {
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
                    if (arena.body[arenaY + row][arenaX + col + 1] != 'X') {
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
                    if (arena.body[arenaY + row + 1][arenaX + col] != 'X') {
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

bool Block::rotationIsPossible(const Arena& arena, const Offset& offset, int rotation) {
    int newX, newY;

    for (int row = 0; row < dimensions; row++) {
        for (int col = 0; col < dimensions; col++) {
            newX = arenaX + offset.x + col;
            newY = arenaY + offset.y + row;
            if (body[rotation][row][col] == '#') {
                if (arena.body[newY][newX] != 'X' || newX < 0 || newX >= columns || newY >= rows) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Block::counterKick(const Arena& arena, int rotation) {
    for (int test = 0; test < 5; test++) {
        if (rotationIsPossible(arena, counterOffset[rotation][test], rotation)) {
            arenaX += counterOffset[rotation][test].x;
            arenaY += counterOffset[rotation][test].y;
            position.x += counterOffset[rotation][test].x * size;
            position.y += counterOffset[rotation][test].y * size;
            rotateCounter();
            break;
        }
    }
}

void Block::clockwiseKick(const Arena& arena, int rotation) {
    for (int test = 0; test < 5; test++) {
        if (rotationIsPossible(arena, clockwiseOffset[rotation][test], rotation)) {
            arenaX += clockwiseOffset[rotation][test].x;
            arenaY += clockwiseOffset[rotation][test].y;
            position.x += clockwiseOffset[rotation][test].x * size;
            position.y += clockwiseOffset[rotation][test].y * size;
            rotateClockwise();
            break;
        }
    }
}