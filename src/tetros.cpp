#include "include/tetros.h"

OBlock::OBlock() {
    dimensions = 2;
    rotation = 0;
    color = YELLOW;
    body[0] = {{
    {'#', '#'},
    {'#', '#'}}};
    body[1] = {{
    {'#', '#'},
    {'#', '#'}}};
    body[2] = {{
    {'#', '#'},
    {'#', '#'}}};
    body[3] = {{
    {'#', '#'},
    {'#', '#'}}};
    centerX = 4;
    centerY = 0;
    position = {static_cast<float>(size * centerX), static_cast<float>(size * centerY)};
}

std::unique_ptr<Block> OBlock::clone() {
    return std::make_unique<OBlock>(*this);
}

bool OBlock::atLeft() {
    return (centerX == 0);
}

bool OBlock::atRight() {
    return (centerX + 1 == columns - 1);
}

bool OBlock::atBottom() {
    return (centerY + 1 == rows - 1);
}

void OBlock::counterKick(const Arena& arena) {}

void OBlock::clockwiseKick(const Arena& arena) {}

IBlock::IBlock() {
    dimensions = 4;
    rotation = 0;
    color = SKYBLUE;
    body[0] = {{
    {'X', 'X', 'X', 'X'},
    {'#', '#', '#', '#'},
    {'X', 'X', 'X', 'X'},
    {'X', 'X', 'X', 'X'}}};
    body[1] = {{
    {'X', 'X', '#', 'X'},
    {'X', 'X', '#', 'X'},
    {'X', 'X', '#', 'X'},
    {'X', 'X', '#', 'X'}}};
    body[2] = {{
    {'X', 'X', 'X', 'X'},
    {'X', 'X', 'X', 'X'},
    {'#', '#', '#', '#'},
    {'X', 'X', 'X', 'X'}}};
    body[3] = {{
    {'X', '#', 'X', 'X'},
    {'X', '#', 'X', 'X'},
    {'X', '#', 'X', 'X'},
    {'X', '#', 'X', 'X'}}};
    centerX = 3;
    centerY = -1;
    position = {static_cast<float>(size * centerX), static_cast<float>(size * centerY)};
}

std::unique_ptr<Block> IBlock::clone() {
    return std::make_unique<IBlock>(*this);
}

bool IBlock::atLeft() {
    switch (rotation) {
        case 0:
        case 2:
            return (centerX == 0);
        break;
        case 1:
            return (centerX + 2 == 0);
        break;
        case 3:
            return (centerX + 1 == 0);
        break;
        default:
            return false;
        break;
    }
}

bool IBlock::atRight() {
    switch (rotation) {
        case 0:
        case 2:
            return (centerX + 3 == columns - 1);
        break;
        case 1:
            return (centerX + 2 == columns - 1);
        break;
        case 3:
            return (centerX + 1 == columns - 1);
        break;
        default:
            return false;
        break;
    }
}

bool IBlock::atBottom() {
    switch (rotation) {
        case 0:
            return (centerY + 1 == rows - 1);
        break;
        case 1:
        case 3:
            return (centerY + 3 == rows - 1);
        break;
        case 2:
            return (centerY + 2 == rows - 1);
        break;
        default:
            return false;
        break;
    }
}

void IBlock::counterKick(const Arena& arena) { 
    rotateCounter();
    for (int test = 0; test < 5; test++) {
        if (rotationIsPossible(arena, ICounterOffset[rotation][test])) {
            centerX += ICounterOffset[rotation][test].x;
            centerY += ICounterOffset[rotation][test].y;
            position.x += ICounterOffset[rotation][test].x * size;
            position.y += ICounterOffset[rotation][test].y * size;
            return;
        }
    }
    rotateClockwise();
}

void IBlock::clockwiseKick(const Arena& arena) {
    rotateClockwise();
    for (int test = 0; test < 5; test++) {
        if (rotationIsPossible(arena, IClockwiseOffset[rotation][test])) {
            centerX += IClockwiseOffset[rotation][test].x;
            centerY += IClockwiseOffset[rotation][test].y;
            position.x += IClockwiseOffset[rotation][test].x * size;
            position.y += IClockwiseOffset[rotation][test].y * size;
            return;
        }
    }
    rotateCounter();
}

SBlock::SBlock() {
    dimensions = 3;
    rotation = 0;
    color = GREEN;
    body[0] = {{
    {'X', '#', '#'},
    {'#', '#', 'X'},
    {'X', 'X', 'X'}}};
    body[1] = {{
    {'X', '#', 'X'},
    {'X', '#', '#'},
    {'X', 'X', '#'}}};
    body[2] = {{
    {'X', 'X', 'X'},
    {'X', '#', '#'},
    {'#', '#', 'X'}}};
    body[3] = {{
    {'#', 'X', 'X'},
    {'#', '#', 'X'},
    {'X', '#', 'X'}}};
    centerX = 4;
    centerY = 0;
    position = {static_cast<float>(size * centerX), static_cast<float>(size * centerY)};
}

std::unique_ptr<Block> SBlock::clone() {
    return std::make_unique<SBlock>(*this);
}

bool SBlock::atLeft() {
    switch (rotation) {
        case 0:
        case 2:
        case 3:
            return (centerX == 0);
        break;
        case 1:
            return (centerX + 1 == 0);
        break;
        default:
            return false;
        break;
    }
}

bool SBlock::atRight() {
    switch (rotation) {
        case 0:
        case 1:
        case 2:
            return (centerX + 2 == columns - 1);
        break;
        case 3:
            return (centerX + 1 == columns - 1);
        break;
        default:
            return false;
        break;
    }
}

bool SBlock::atBottom() {
    switch (rotation) {
        case 0:
            return (centerY + 1 == rows - 1);
        break;
        case 1:
        case 2:
        case 3:
            return (centerY + 2 == rows - 1);
        break;
        default:
            return false;
        break;
    }
}

ZBlock::ZBlock() {
    dimensions = 3;
    rotation = 0;
    color = RED;
    body[0] = {{
    {'#', '#', 'X'},
    {'X', '#', '#'},
    {'X', 'X', 'X'}}};
    body[1] = {{
    {'X', 'X', '#'},
    {'X', '#', '#'},
    {'X', '#', 'X'}}};
    body[2] = {{
    {'X', 'X', 'X'},
    {'#', '#', 'X'},
    {'X', '#', '#'}}};
    body[3] = {{
    {'X', '#', 'X'},
    {'#', '#', 'X'},
    {'#', 'X', 'X'}}};
    centerX = 4;
    centerY = 0;
    position = {static_cast<float>(size * centerX), static_cast<float>(size * centerY)};
}

std::unique_ptr<Block> ZBlock::clone() {
    return std::make_unique<ZBlock>(*this);
}

bool ZBlock::atLeft() {
    switch (rotation) {
        case 0:
        case 2:
        case 3:
            return (centerX == 0);
        break;
        case 1:
            return (centerX + 1 == 0);
        break;
        default:
            return false;
        break;
    }
}

bool ZBlock::atRight() {
    switch (rotation) {
        case 0:
        case 1:
        case 2:
            return (centerX + 2 == columns - 1);
        break;
        case 3:
            return (centerX + 1 == columns - 1);
        break;
        default:
            return false;
        break;
    }
}

bool ZBlock::atBottom() {
    switch (rotation) {
        case 0:
            return (centerY + 1 == rows - 1);
        break;
        case 1:
        case 2:
        case 3:
            return (centerY + 2 == rows - 1);
        break;
        default:
            return false;
        break;
    }
}

LBlock::LBlock() {
    dimensions = 3;
    rotation = 0;
    color = ORANGE;
    body[0] = {{
    {'X', 'X', '#'},
    {'#', '#', '#'},
    {'X', 'X', 'X'}}};
    body[1] = {{
    {'X', '#', 'X'},
    {'X', '#', 'X'},
    {'X', '#', '#'}}};
    body[2] = {{
    {'X', 'X', 'X'},
    {'#', '#', '#'},
    {'#', 'X', 'X'}}};
    body[3] = {{
    {'#', '#', 'X'},
    {'X', '#', 'X'},
    {'X', '#', 'X'}}};
    centerX = 4;
    centerY = 0;
    position = {static_cast<float>(size * centerX), static_cast<float>(size * centerY)};
}

std::unique_ptr<Block> LBlock::clone() {
    return std::make_unique<LBlock>(*this);
}

bool LBlock::atLeft() {
    switch (rotation) {
        case 0:
        case 2:
        case 3:
            return (centerX == 0);
        break;
        case 1:
            return (centerX + 1 == 0);
        break;
        default:
            return false;
        break;
    }
}

bool LBlock::atRight() {
    switch (rotation) {
        case 0:
        case 1:
        case 2:
            return (centerX + 2 == columns - 1);
        break;
        case 3:
            return (centerX + 1 == columns - 1);
        break;
        default:
            return false;
        break;
    }
}

bool LBlock::atBottom() {
    switch (rotation) {
        case 0:
            return (centerY + 1 == rows - 1);
        break;
        case 1:
        case 2:
        case 3:
            return (centerY + 2 == rows - 1);
        break;
        default:
            return false;
        break;
    }
}

JBlock::JBlock() {
    dimensions = 3;
    rotation = 0;
    color = BLUE;
    body[0] = {{
    {'X', 'X', 'X'},
    {'#', '#', '#'},
    {'X', 'X', '#'}}};
    body[1] = {{
    {'X', '#', 'X'},
    {'X', '#', 'X'},
    {'#', '#', 'X'}}};
    body[2] = {{
    {'#', 'X', 'X'},
    {'#', '#', '#'},
    {'X', 'X', 'X'}}};
    body[3] = {{
    {'X', '#', '#'},
    {'X', '#', 'X'},
    {'X', '#', 'X'}
    }};
    centerX = 4;
    centerY = -1;
    position = {static_cast<float>(size * centerX), static_cast<float>(size * centerY)};
}

std::unique_ptr<Block> JBlock::clone() {
    return std::make_unique<JBlock>(*this);
}

bool JBlock::atLeft() {
    switch (rotation) {
        case 0:
        case 1:
        case 2:
            return (centerX == 0);
        break;
        case 3:
            return (centerX + 1 == 0);
        break;
        default:
            return false;
        break;
    }
}

bool JBlock::atRight() {
    switch (rotation) {
        case 0:
        case 2:
        case 3:
            return (centerX + 2 == columns - 1);
        break;
        case 1:
            return (centerX + 1 == columns - 1);
        break;
        default:
            return false;
        break;
    }
}

bool JBlock::atBottom() {
    switch (rotation) {
        case 0:
        case 1:
        case 3:
            return (centerY + 2 == rows - 1);
        break;
        case 2:
            return (centerY + 1 == rows - 1);
        break;
        default:
            return false;
        break;
    }
}

TBlock::TBlock() {
    dimensions = 3;
    rotation = 0;
    color = VIOLET;
    body[0] = {{
    {'X', '#', 'X'},
    {'#', '#', '#'},
    {'X', 'X', 'X'}}};
    body[1] = {{
    {'X', '#', 'X'},
    {'X', '#', '#'},
    {'X', '#', 'X'}}};
    body[2] = {{
    {'X', 'X', 'X'},
    {'#', '#', '#'},
    {'X', '#', 'X'}}};
    body[3] = {{
    {'X', '#', 'X'},
    {'#', '#', 'X'},
    {'X', '#', 'X'}}};
    centerX = 4;
    centerY = 0;
    position = {static_cast<float>(size * centerX), static_cast<float>(size * centerY)};
}

std::unique_ptr<Block> TBlock::clone() {
    return std::make_unique<TBlock>(*this);
}

bool TBlock::atLeft() {
    switch (rotation) {
        case 0:
        case 2:
        case 3:
            return (centerX == 0);
        break;
        case 1:
            return (centerX + 1 == 0);
        break;
        default:
            return false;
        break;
    }
}

bool TBlock::atRight() {
    switch (rotation) {
        case 0:
        case 1:
        case 2:
            return (centerX + 2 == columns - 1);
        break;
        case 3:
            return (centerX + 1 == columns - 1);
        break;
        default:
            return false;
        break;
    }
}

bool TBlock::atBottom() {
    switch (rotation) {
        case 0:
            return (centerY + 1 == rows - 1);
        break;
        case 1:
        case 2:
        case 3:
            return (centerY + 2 == rows - 1);
        break;
        default:
            return false;
        break;
    }
}