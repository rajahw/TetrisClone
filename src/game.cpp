#include "include/game.h"

Game::Game() {
    blockType = BlockEnum::O;
    nextBlockType = BlockEnum::O;
    blockBag = BlockEnum::O;
    numCleared = 0;
    rowsCleared = 0;
    levelCleared = 0;
    score = 0;
    highScore = 0;
    speed = 1;
    fps = 0;
    blockMoving = false;
    locking = false;
    exitWindow = false;
    gameOver = false;
    paused = false;
    speedIncreased = false;
    grayOutUpdated = false;
    loseSoundPlayed = false;
    blocks = {BlockEnum::O, BlockEnum::I, BlockEnum::S, BlockEnum::Z, BlockEnum::L, BlockEnum::J, BlockEnum::T};
    mouseLocation = {0.0f, 0.0f};
    gameOverScreen = {0, 0, 0, 200};
    yesHitbox = {130.0f * windowScale, 900.0f * windowScale, 220.0f * windowScale, 90.0f * windowScale};
    noHitbox = {130.0f * windowScale, 1000.0f * windowScale, 160.0f * windowScale, 90.0f * windowScale};
    firstBlock();
}

void Game::run() {
    if (IsKeyPressed(KEY_BACKSPACE)) {
        if (!paused) {
            updateGrayOut();
            PauseMusicStream(music);
            PlaySound(openMenu);
            paused = true;
        } else {
            PlaySound(selectMenu);
            ResumeMusicStream(music);
            paused = false;
        }
    }

    if (WindowShouldClose()) {
        exitWindow = true;
    }

    fps = GetFPS();

    gameOver = gameIsOver();

    if (!gameOver) {
        if (!paused) {
            rotateInput(currentBlock);

            if (timePassed(moveInterval, moveUpdate)) {
                moveInput(currentBlock);
            }

            if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_D) && !IsKeyDown(KEY_RIGHT)) {
                blockMoving = false;
            }

            if (timePassed(downInterval, downUpdate) && !currentBlock->collidingBottom(arena) && !IsKeyDown(KEY_S) && !IsKeyDown(KEY_DOWN)) {
                currentBlock->moveDown();
            }

            if (currentBlock->atBottom() || currentBlock->collidingBottom(arena)) {
                if (!locking && blockMoving) {
                    locking = true;
                    lockUpdate = GetTime();
                }

                if (timePassed(lockInterval, lockUpdate)) {
                    updateArena();
                    clearRows();
                    spawnBlock();
                    locking = false;
                }
            } else {
                locking = false;
            }

            if (score > highScore) {
                highScore = score;
            }

            updatePanel();

            arena.draw();
            drawPanel();
            drawNextBlock();
            currentBlock->draw();
        } else {
            grayOut.draw();
            drawPanel();
            drawPause();
        }
    } else {

        if (!loseSoundPlayed) {
            PauseMusicStream(music);
            PlaySound(loseSound);
            loseSoundPlayed = true;
        }

        if (!grayOutUpdated) {
            updateGrayOut();
            grayOutUpdated = true;
        }

        mouseLocation = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouseLocation, yesHitbox)) {
            PlaySound(selectMenu);
            ResumeMusicStream(music);
            reset();
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouseLocation, noHitbox)) {
            PlaySound(selectMenu);
            exitWindow = true;
        }

        grayOut.draw();
        drawPanel();
        drawGameOver();
    }
}

void Game::reset() {
    blockType = BlockEnum::O;
    nextBlockType = BlockEnum::O;
    blockBag = BlockEnum::O;
    numCleared = 0;
    rowsCleared = 0;
    levelCleared = 0;
    score = 0;
    speed = 1;
    fps = 0;
    scoreMultiplier = 1.0;
    downInterval = 0.55;
    blockMoving = false;
    locking = false;
    exitWindow = false;
    gameOver = false;
    paused = false;
    speedIncreased = false;
    grayOutUpdated = false;
    loseSoundPlayed = false;
    blocks = {BlockEnum::O, BlockEnum::I, BlockEnum::S, BlockEnum::Z, BlockEnum::L, BlockEnum::J, BlockEnum::T};
    arena.initialize();
    grayOut.initialize();
    firstBlock();
}

void Game::loadAssets() {
    font = GetFontDefault();
    music = LoadMusicStream("assets/music.mp3");
    loseSound = LoadSound("assets/loss.wav");
    openMenu = LoadSound("assets/menuopen.wav");
    selectMenu = LoadSound("assets/menuselect.wav");
    scoreSound = LoadSound("assets/score.wav");
    speedIncreaseSound = LoadSound("assets/speedincrease.wav");
}

void Game::unloadAssets() {
    UnloadFont(font);
    UnloadMusicStream(music);
    UnloadSound(loseSound);
    UnloadSound(openMenu);
    UnloadSound(selectMenu);
    UnloadSound(scoreSound);
    UnloadSound(speedIncreaseSound);
}

void Game::moveInput(const std::unique_ptr<Block>& block) {
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        blockMoving = true;
        if (!block->collidingLeft(arena)) {
            block->moveLeft();
        }
    }

    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        if (!block->collidingBottom(arena) && !block->atBottom()) {
            block->moveDown();
            score += 2;
        }
    }

    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        blockMoving = true;
        if (!block->collidingRight(arena)) {
            block->moveRight();
        }
    }
}

void Game::rotateInput(const std::unique_ptr<Block>& block) {
    if (IsKeyPressed(KEY_O) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
        blockMoving = true;
        block->counterKick(arena);
    }

    if (IsKeyPressed(KEY_P)) {
        blockMoving = true;
        block->clockwiseKick(arena);
    }
}

void Game::updateArena() {
    for (int row = 0; row < currentBlock->dimensions; row++) {
        for (int col = 0; col < currentBlock->dimensions; col++) {
            if (currentBlock->body[currentBlock->rotation][row][col] == '#') {
                switch (blockType) {
                    case BlockEnum::O:
                        arena.body[currentBlock->centerY + row][currentBlock->centerX + col] = 'O';
                    break;
                    case BlockEnum::I:
                        arena.body[currentBlock->centerY + row][currentBlock->centerX + col] = 'I';
                    break;
                    case BlockEnum::S:
                        arena.body[currentBlock->centerY + row][currentBlock->centerX + col] = 'S';
                    break;
                    case BlockEnum::Z:
                        arena.body[currentBlock->centerY + row][currentBlock->centerX + col] = 'Z';
                    break;
                    case BlockEnum::L:
                        arena.body[currentBlock->centerY + row][currentBlock->centerX + col] = 'L';
                    break;
                    case BlockEnum::J:
                        arena.body[currentBlock->centerY + row][currentBlock->centerX + col] = 'J';
                    break;
                    case BlockEnum::T:
                        arena.body[currentBlock->centerY + row][currentBlock->centerX + col] = 'T';
                    break;
                }
            }
        }
    }
}

void Game::updateGrayOut() {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            if (arena.body[row][col] != 'X') {
                grayOut.body[row][col] = 'G';
            }
        }
    }
}

void Game::drawGameOver() {
    DrawRectangle(0, 0, width * 1.75, height, gameOverScreen);
    DrawTextEx(font, "GAME OVER!", {150 * windowScale, 500 * windowScale}, 200.0f * windowScale, 5.0f * windowScale, RED);
    DrawTextEx(font, "Play again?", {150 * windowScale, 700 * windowScale}, 150.0f * windowScale, 4.0f * windowScale, LIGHTGRAY);

    if (CheckCollisionPointRec(mouseLocation, yesHitbox)) {
        DrawTextEx(font, "YES", {150 * windowScale, 900 * windowScale}, 100.0f * windowScale, 3.0f * windowScale, RED);
    } else {
        DrawTextEx(font, "YES", {150 * windowScale, 900 * windowScale}, 100.0f * windowScale, 3.0f * windowScale, LIGHTGRAY);
    }

    if (CheckCollisionPointRec(mouseLocation, noHitbox)) {
        DrawTextEx(font, "NO", {150 * windowScale, 1000 * windowScale}, 100.0f * windowScale, 3.0f * windowScale, RED);
    } else {
        DrawTextEx(font, "NO", {150 * windowScale, 1000 * windowScale}, 100.0f * windowScale, 3.0f * windowScale, LIGHTGRAY);
    }
}

void Game::drawPause() {
    DrawRectangle(0, 0, width * 1.75, height, gameOverScreen);
    DrawTextEx(font, "BACKSPACE to\nresume", {150 * windowScale, 200 * windowScale}, 150.0f * windowScale, 4.0f * windowScale, RED);
    DrawTextEx(font, "SFX Credits:", {150 * windowScale, 700 * windowScale}, 100.0f * windowScale, 3.0f * windowScale, LIGHTGRAY);
    DrawTextEx(font, "Ethernight Club -- Kevin MacLeod\nAction 01 -- rhodesmas\nAction 02 -- rhodesmas\nDisconnected 01 -- rhodesmas\nUI Button Press -- el_boss\nCancel or No Button Sound -- el_boss", {150 * windowScale, 800 * windowScale}, 70.0f * windowScale, 2.0f * windowScale, LIGHTGRAY);
}

void Game::drawPanel() {
    DrawTextEx(font, "Next Block", {width + 50 * windowScale, 0}, 75.0f * windowScale, 2.0f * windowScale, BLACK);
    DrawRectangle(width + 50 * windowScale, 75 * windowScale, size * 5, size * 5, BLACK);
    DrawTextEx(font, "Score", {width + 50 * windowScale, 500 * windowScale}, 75.0f * windowScale, 2.0f * windowScale, BLACK);
    DrawTextEx(font, scoreString, {width + 50 * windowScale, 575 * windowScale}, 75.0f * windowScale, 2.0f * windowScale, RED);
    DrawTextEx(font, "High Score", {width + 50 * windowScale, 700 * windowScale}, 75.0f * windowScale, 2.0f * windowScale, BLACK);
    DrawTextEx(font, highScoreString, {width + 50 * windowScale, 775 * windowScale}, 75.0f * windowScale, 2.0f * windowScale, RED);
    DrawTextEx(font, "Rows Cleared", {width + 50 * windowScale, 900 * windowScale}, 75.0f * windowScale, 2.0f * windowScale, BLACK);
    DrawTextEx(font, rowsClearedString, {width + 50 * windowScale, 975 * windowScale}, 75.0f * windowScale, 2.0f * windowScale, RED);
    DrawRectangle(width + 50 * windowScale, 1050 * windowScale, size * 6.5, size * 4.5, BLACK);
    DrawTextEx(font, "Controls", {width + 60 * windowScale, 1055 * windowScale}, 75.0f * windowScale, 2.0f * windowScale, RED);
    DrawTextEx(font, "Move: A, S, D, Arrows", {width + 60 * windowScale, 1125 * windowScale}, 50.0f * windowScale, 2.0f * windowScale, LIGHTGRAY);
    DrawTextEx(font, "Rotate Left: W, Up, O", {width + 60 * windowScale, 1200 * windowScale}, 50.0f * windowScale, 2.0f * windowScale, LIGHTGRAY);
    DrawTextEx(font, "Rotate Right: P", {width + 60 * windowScale, 1275 * windowScale}, 50.0f * windowScale, 2.0f * windowScale, LIGHTGRAY);
    DrawTextEx(font, "Pause: Backspace", {width + 60 * windowScale, 1350 * windowScale}, 50.0f * windowScale, 2.0f * windowScale, LIGHTGRAY);
    DrawTextEx(font, fpsString, {width + 500 * windowScale, 0}, 75.0f * windowScale, 2.0f * windowScale, RED);
}

void Game::drawNextBlock() {
    panelBlock->position.x = width + 50 * windowScale + (size * 5 - (panelBlock->dimensions * size)) / 2;
    panelBlock->position.y = 75 * windowScale + (size * 5 - (panelBlock->dimensions * size)) / 2;
    panelBlock->draw();
}

void Game::updatePanel() {
    sprintf(fpsString, "%d", fps);
    sprintf(scoreString, "%d", score);
    sprintf(highScoreString, "%d", highScore);
    sprintf(rowsClearedString, "%d", rowsCleared);
}

bool Game::rowFull(int checkedRow) {
    for (int col = 0; col < columns; col++) {
        if (arena.body[checkedRow][col] == 'X') {
            return false;
        }
    }
    return true;
}

void Game::clearRows() {
    numCleared = 0;

    int copiedRow = rows - 1;

    for (int row = rows - 1; row >= 0; row--) {
        if (!rowFull(row)) {
            for (int col = 0; col < columns; col++) {
                arena.body[copiedRow][col] = arena.body[row][col];
            }
            copiedRow--;
        } else {
            levelCleared = row;
            numCleared++;
        }
    }

    for (int row = copiedRow; row >= 0; row--) {
        for (int col = 0; col < columns; col++) {
            arena.body[row][col] = 'X';
        }
    }

    if (numCleared > 0) {
        switch (numCleared) {
            case 1:
                score += 100 * (20 - levelCleared) * scoreMultiplier;
            break;
            case 2:
                score += 300 * (20 - levelCleared) * scoreMultiplier;
            break;
            case 3:
                score += 500 * (20 - levelCleared) * scoreMultiplier;
            break;
            case 4:
                score += 800 * (20 - levelCleared) * scoreMultiplier;
            break;
            default: break;
        }

        if (speedIncreased) {
            speedIncreased = false;
        }

        if (static_cast<float>(rowsCleared + numCleared) / speed >= 10 && speed <= 10 && !speedIncreased) {
            PlaySound(speedIncreaseSound);
            increaseSpeed();
        } else {
            PlaySound(scoreSound);
        }

        rowsCleared += numCleared;
    }
}

bool Game::gameIsOver() {
    for (int col = 0; col < columns; col++) {
        if (arena.body[0][col] != 'X') {
            return true;
        }
    }
    return false;
}

void Game::getNextBlock(BlockEnum& type) {
    if (blocks.empty()) {blocks = {BlockEnum::O, BlockEnum::I, BlockEnum::S, BlockEnum::Z, BlockEnum::L, BlockEnum::J, BlockEnum::T};}

    int index = GetRandomValue(0, blocks.size() - 1);

    type = blocks[index];

    blocks.erase(blocks.begin() + index);
}

void Game::firstBlock() {
    getNextBlock(blockBag);
    blockType = blockBag;
    switch (blockType) {
        case BlockEnum::O:
            currentBlock = std::make_unique<OBlock>();
        break;
        case BlockEnum::I:
            currentBlock = std::make_unique<IBlock>();
        break;
        case BlockEnum::S:
            currentBlock = std::make_unique<SBlock>();
        break;
        case BlockEnum::Z:
            currentBlock = std::make_unique<ZBlock>();
        break;
        case BlockEnum::L:
            currentBlock = std::make_unique<LBlock>();
        break;
        case BlockEnum::J:
            currentBlock = std::make_unique<JBlock>();
        break;
        case BlockEnum::T:
            currentBlock = std::make_unique<TBlock>();
        break;
    }

    getNextBlock(blockBag);
    nextBlockType = blockBag;
    switch (nextBlockType) {
        case BlockEnum::O:
            nextBlock = std::make_unique<OBlock>();
        break;
        case BlockEnum::I:
            nextBlock = std::make_unique<IBlock>();
        break;
        case BlockEnum::S:
            nextBlock = std::make_unique<SBlock>();
        break;
        case BlockEnum::Z:
            nextBlock = std::make_unique<ZBlock>();
        break;
        case BlockEnum::L:
            nextBlock = std::make_unique<LBlock>();
        break;
        case BlockEnum::J:
            nextBlock = std::make_unique<JBlock>();
        break;
        case BlockEnum::T:
            nextBlock = std::make_unique<TBlock>();
        break;
    }

    panelBlock = nextBlock->clone();
}

void Game::spawnBlock() {
    currentBlock = nextBlock->clone();
    blockType = nextBlockType;
    
    getNextBlock(blockBag);
    nextBlockType = blockBag;
    switch (nextBlockType) {
        case BlockEnum::O:
            nextBlock = std::make_unique<OBlock>();
        break;
        case BlockEnum::I:
            nextBlock = std::make_unique<IBlock>();
        break;
        case BlockEnum::S:
            nextBlock = std::make_unique<SBlock>();
        break;
        case BlockEnum::Z:
            nextBlock = std::make_unique<ZBlock>();
        break;
        case BlockEnum::L:
            nextBlock = std::make_unique<LBlock>();
        break;
        case BlockEnum::J:
            nextBlock = std::make_unique<JBlock>();
        break;
        case BlockEnum::T:
            nextBlock = std::make_unique<TBlock>();
        break;
    }

    panelBlock = nextBlock->clone();
}

bool Game::timePassed(double span, double& updateTime) {
    double time = GetTime();
    if (time - updateTime >= span) {
        updateTime = time;
        return true;
    } else {
        return false;
    }
}

void Game::increaseSpeed() {
    downInterval -= 0.05;
    scoreMultiplier += 0.05;
    speed++;
    speedIncreased = true;
}