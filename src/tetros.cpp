#include "tetros.h"

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
    arenaX = 4;
    arenaY = 0;
    position = {static_cast<float>(size * arenaX), static_cast<float>(size * arenaY)};
    isGhost = false;
}

std::unique_ptr<Block> OBlock::clone() {
    return std::make_unique<OBlock>(*this);
}

bool OBlock::atLeft() {
    if (arenaX == 0) {
        return true;
    } else {
        return false;
    }
}

bool OBlock::atRight() {
    if (arenaX + 1 == columns - 1) {
        return true;
    } else {
        return false;
    }
}

bool OBlock::atBottom() {
    if (arenaY + 1 == rows - 1) {
        return true;
    } else {
        return false;
    }
}

void OBlock::counterKick(const Arena& arena, int rotation) {}

void OBlock::clockwiseKick(const Arena& arena, int rotation) {}

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
    arenaX = 3;
    arenaY = -1;
    position = {static_cast<float>(size * arenaX), static_cast<float>(size * arenaY)};
    isGhost = false;
}

std::unique_ptr<Block> IBlock::clone() {
    return std::make_unique<IBlock>(*this);
}

bool IBlock::atLeft() {
    switch (rotation) {
        case 0:
            if (arenaX == 0) {
                return true;
            } else {
                return false;
            }
        break;
        case 1:
            if (arenaX + 2 == 0) {
                return true;
            } else {
                return false;
            }
        break;
        case 2:
            if (arenaX == 0) {
                return true;
            } else {
                return false;
            }
        break;
        case 3:
            if (arenaX + 1 == 0) {
                return true;
            } else {
                return false;
            }
        break;
        default:
            return false;
        break;
    }
}

bool IBlock::atRight() {
    switch (rotation) {
        case 0:
            if (arenaX + 3 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 1:
            if (arenaX + 2 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 2:
            if (arenaX + 3 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 3:
            if (arenaX + 1 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        default:
            return false;
        break;
    }
}

bool IBlock::atBottom() {
    switch (rotation) {
        case 0:
            if (arenaY + 1 == rows - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 1:
            if (arenaY + 3 == rows - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 2:
            if (arenaY + 2 == rows - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 3:
            if (arenaY + 3 == rows - 1) {
                return true;
            } else {
                return false;
            }
        break;
        default:
            return false;
        break;
    }
}

void IBlock::counterKick(const Arena& arena, int rotation) {
    for (int test = 0; test < 5; test++) {
        if (rotationIsPossible(arena, ICounterOffset[rotation][test], rotation)) {
            arenaX += ICounterOffset[rotation][test].x;
            arenaY += ICounterOffset[rotation][test].y;
            position.x += ICounterOffset[rotation][test].x * size;
            position.y += ICounterOffset[rotation][test].y * size;
            rotateCounter();
            break;
        }
    }
}

void IBlock::clockwiseKick(const Arena& arena, int rotation) {
    for (int test = 0; test < 5; test++) {
        if (rotationIsPossible(arena, IClockwiseOffset[rotation][test], rotation)) {
            arenaX += IClockwiseOffset[rotation][test].x;
            arenaY += IClockwiseOffset[rotation][test].y;
            position.x += IClockwiseOffset[rotation][test].x * size;
            position.y += IClockwiseOffset[rotation][test].y * size;
            rotateClockwise();
            break;
        }
    }
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
    arenaX = 4;
    arenaY = 0;
    position = {static_cast<float>(size * arenaX), static_cast<float>(size * arenaY)};
    isGhost = false;
}

std::unique_ptr<Block> SBlock::clone() {
    return std::make_unique<SBlock>(*this);
}

bool SBlock::atLeft() {
    switch (rotation) {
        case 0:
            if (arenaX == 0) {
                return true;
            } else {
                return false;
            }
        break;
        case 1:
            if (arenaX + 1 == 0) {
                return true;
            } else {
                return false;
            }
        break;
        case 2:
            if (arenaX == 0) {
                return true;
            } else {
                return false;
            }
        break;
        case 3:
            if (arenaX == 0) {
                return true;
            } else {
                return false;
            }
        break;
        default:
            return false;
        break;
    }
}

bool SBlock::atRight() {
    switch (rotation) {
        case 0:
            if (arenaX + 2 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 1:
            if (arenaX + 2 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 2:
            if (arenaX + 2 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 3:
            if (arenaX + 1 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        default:
            return false;
        break;
    }
}

bool SBlock::atBottom() {
    switch (rotation) {
        case 0:
            if (arenaY + 1 == rows - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 1:
            if (arenaY + 2 == rows - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 2:
            if (arenaY + 2 == rows - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 3:
            if (arenaY + 2 == rows - 1) {
                return true;
            } else {
                return false;
            }
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
    arenaX = 4;
    arenaY = 0;
    position = {static_cast<float>(size * arenaX), static_cast<float>(size * arenaY)};
    isGhost = false;
}

std::unique_ptr<Block> ZBlock::clone() {
    return std::make_unique<ZBlock>(*this);
}

bool ZBlock::atLeft() {
    switch (rotation) {
        case 0:
            if (arenaX == 0) {
                return true;
            } else {
                return false;
            }
        break;
        case 1:
            if (arenaX + 1 == 0) {
                return true;
            } else {
                return false;
            }
        break;
        case 2:
            if (arenaX == 0) {
                return true;
            } else {
                return false;
            }
        break;
        case 3:
            if (arenaX == 0) {
                return true;
            } else {
                return false;
            }
        break;
        default:
            return false;
        break;
    }
}

bool ZBlock::atRight() {
    switch (rotation) {
        case 0:
            if (arenaX + 2 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 1:
            if (arenaX + 2 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 2:
            if (arenaX + 2 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 3:
            if (arenaX + 1 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        default:
            return false;
        break;
    }
}

bool ZBlock::atBottom() {
    switch (rotation) {
        case 0:
            if (arenaY + 1 == rows - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 1:
            if (arenaY + 2 == rows - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 2:
            if (arenaY + 2 == rows - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 3:
            if (arenaY + 2 == rows - 1) {
                return true;
            } else {
                return false;
            }
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
    arenaX = 4;
    arenaY = 0;
    position = {static_cast<float>(size * arenaX), static_cast<float>(size * arenaY)};
    isGhost = false;
}

std::unique_ptr<Block> LBlock::clone() {
    return std::make_unique<LBlock>(*this);
}

bool LBlock::atLeft() {
    switch (rotation) {
        case 0:
            if (arenaX == 0) {
                return true;
            } else {
                return false;
            }
        break;
        case 1:
            if (arenaX + 1 == 0) {
                return true;
            } else {
                return false;
            }
        break;
        case 2:
            if (arenaX == 0) {
                return true;
            } else {
                return false;
            }
        break;
        case 3:
            if (arenaX == 0) {
                return true;
            } else {
                return false;
            }
        break;
        default:
            return false;
        break;
    }
}

bool LBlock::atRight() {
    switch (rotation) {
        case 0:
            if (arenaX + 2 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 1:
            if (arenaX + 2 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 2:
            if (arenaX + 2 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 3:
            if (arenaX + 1 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        default:
            return false;
        break;
    }
}

bool LBlock::atBottom() {
    switch (rotation) {
        case 0:
            if (arenaY + 1 == rows - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 1:
            if (arenaY + 2 == rows - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 2:
            if (arenaY + 2 == rows - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 3:
            if (arenaY + 2 == rows - 1) {
                return true;
            } else {
                return false;
            }
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
    arenaX = 4;
    arenaY = -1;
    position = {static_cast<float>(size * arenaX), static_cast<float>(size * arenaY)};
    isGhost = false;
}

std::unique_ptr<Block> JBlock::clone() {
    return std::make_unique<JBlock>(*this);
}

bool JBlock::atLeft() {
    switch (rotation) {
        case 0:
            if (arenaX == 0) {
                return true;
            } else {
                return false;
            }
        break;
        case 1:
            if (arenaX == 0) {
                return true;
            } else {
                return false;
            }
        break;
        case 2:
            if (arenaX == 0) {
                return true;
            } else {
                return false;
            }
        break;
        case 3:
            if (arenaX + 1 == 0) {
                return true;
            } else {
                return false;
            }
        break;
        default:
            return false;
        break;
    }
}

bool JBlock::atRight() {
    switch (rotation) {
        case 0:
            if (arenaX + 2 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 1:
            if (arenaX + 1 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 2:
            if (arenaX + 2 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 3:
            if (arenaX + 2 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        default:
            return false;
        break;
    }
}

bool JBlock::atBottom() {
    switch (rotation) {
        case 0:
            if (arenaY + 2 == rows - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 1:
            if (arenaY + 2 == rows - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 2:
            if (arenaY + 1 == rows - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 3:
            if (arenaY + 2 == rows - 1) {
                return true;
            } else {
                return false;
            }
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
    arenaX = 4;
    arenaY = 0;
    position = {static_cast<float>(size * arenaX), static_cast<float>(size * arenaY)};
}

std::unique_ptr<Block> TBlock::clone() {
    return std::make_unique<TBlock>(*this);
}

bool TBlock::atLeft() {
    switch (rotation) {
        case 0:
            if (arenaX == 0) {
                return true;
            } else {
                return false;
            }
        break;
        case 1:
            if (arenaX + 1 == 0) {
                return true;
            } else {
                return false;
            }
        break;
        case 2:
            if (arenaX == 0) {
                return true;
            } else {
                return false;
            }
        break;
        case 3:
            if (arenaX == 0) {
                return true;
            } else {
                return false;
            }
        break;
        default:
            return false;
        break;
    }
}

bool TBlock::atRight() {
    switch (rotation) {
        case 0:
            if (arenaX + 2 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 1:
            if (arenaX + 2 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 2:
            if (arenaX + 2 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 3:
            if (arenaX + 1 == columns - 1) {
                return true;
            } else {
                return false;
            }
        break;
        default:
            return false;
        break;
    }
}

bool TBlock::atBottom() {
    switch (rotation) {
        case 0:
            if (arenaY + 1 == rows - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 1:
            if (arenaY + 2 == rows - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 2:
            if (arenaY + 2 == rows - 1) {
                return true;
            } else {
                return false;
            }
        break;
        case 3:
            if (arenaY + 2 == rows - 1) {
                return true;
            } else {
                return false;
            }
        break;
        default:
            return false;
        break;
    }
}