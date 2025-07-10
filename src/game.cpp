#include "include/game.h"

Game::Game() {
    blockType = 0;
    nextBlockType = 0;
    blockBag = 0;
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
    blocks = {0, 1, 2, 3, 4, 5, 6};
    mouseLocation = {0.0f, 0.0f};
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

            if (timePassed(inputInterval, inputUpdate)) {
                moveInput(currentBlock);
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

            increaseSpeed();
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
    blockType = 0;
    nextBlockType = 0;
    blockBag = 0;
    numCleared = 0;
    rowsCleared = 0;
    levelCleared = 0;
    score = 0;
    highScore = 0;
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
    blocks = {0, 1, 2, 3, 4, 5, 6};
    arena.initialize();
    grayOut.initialize();
    firstBlock();
}

void Game::loadAssets() {
    font = LoadFont("resources/fonts/alpha_beta.png");
    music = LoadMusicStream("sfx/music.mp3");
    loseSound = LoadSound("sfx/loss.wav");
    openMenu = LoadSound("sfx/menuopen.wav");
    selectMenu = LoadSound("sfx/menuselect.wav");
    scoreSound = LoadSound("sfx/score.wav");
    speedIncreaseSound = LoadSound("sfx/speedincrease.wav");
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
        if (!block->collidingBottom(arena)) {
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

    if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_D) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_S) && !IsKeyDown(KEY_DOWN)) {
        blockMoving = false;
    }

    if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_D) && !IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_S) && IsKeyDown(KEY_DOWN)) {
        blockMoving = false;
    }
}

void Game::rotateInput(const std::unique_ptr<Block>& block) {
    if (IsKeyPressed(KEY_O) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
        blockMoving = true;

        int nextRotation;

        if (block->rotation > 0) {
            nextRotation = block->rotation - 1;
        } else {
            nextRotation = 3;
        }

        block->counterKick(arena, nextRotation);
    }

    if (IsKeyPressed(KEY_P)) {
        blockMoving = true;

        int nextRotation;

        if (block->rotation < 3) {
            nextRotation = block->rotation + 1;
        } else {
            nextRotation = 0;
        }

        block->clockwiseKick(arena, nextRotation);
    }

    if (!IsKeyPressed(KEY_O) && !IsKeyPressed(KEY_W) && !IsKeyPressed(KEY_UP) && !IsKeyDown(KEY_P)) {
        blockMoving = false;
    }
}

void Game::updateArena() {
    for (int row = 0; row < currentBlock->dimensions; row++) {
        for (int col = 0; col < currentBlock->dimensions; col++) {
            if (currentBlock->body[currentBlock->rotation][row][col] == '#') {
                switch (blockType) {
                    case 0:
                        arena.body[currentBlock->arenaY + row][currentBlock->arenaX + col] = 'O';
                    break;
                    case 1:
                        arena.body[currentBlock->arenaY + row][currentBlock->arenaX + col] = 'I';
                    break;
                    case 2:
                        arena.body[currentBlock->arenaY + row][currentBlock->arenaX + col] = 'S';
                    break;
                    case 3:
                        arena.body[currentBlock->arenaY + row][currentBlock->arenaX + col] = 'Z';
                    break;
                    case 4:
                        arena.body[currentBlock->arenaY + row][currentBlock->arenaX + col] = 'L';
                    break;
                    case 5:
                        arena.body[currentBlock->arenaY + row][currentBlock->arenaX + col] = 'J';
                    break;
                    case 6:
                        arena.body[currentBlock->arenaY + row][currentBlock->arenaX + col] = 'T';
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
    DrawRectangle(0, 0, width + 600, height, gameOverScreen);
    DrawTextEx(font, "GAME OVER!", {150, 500}, 200.0f, 5.0f, RED);
    DrawTextEx(font, "Play again?", {150, 700}, 150.0f, 4.0f, LIGHTGRAY);

    if (CheckCollisionPointRec(mouseLocation, yesHitbox)) {
        DrawTextEx(font, "YES", {150, 900}, 100.0f, 3.0f, RED);
    } else {
        DrawTextEx(font, "YES", {150, 900}, 100.0f, 3.0f, LIGHTGRAY);
    }

    if (CheckCollisionPointRec(mouseLocation, noHitbox)) {
        DrawTextEx(font, "NO", {150, 1000}, 100.0f, 3.0f, RED);
    } else {
        DrawTextEx(font, "NO", {150, 1000}, 100.0f, 3.0f, LIGHTGRAY);
    }
}

void Game::drawPause() {
    DrawRectangle(0, 0, width + 600, height, gameOverScreen);
    DrawTextEx(font, "BACKSPACE to\nresume", {150, 200}, 150.0f, 4.0f, RED);
    DrawTextEx(font, "SFX Credits:", {150, 700}, 100.0f, 3.0f, LIGHTGRAY);
    DrawTextEx(font, "Ethernight Club -- Kevin MacLeod\nAction 01 -- rhodesmas\nAction 02 -- rhodesmas\nDisconnected 01 -- rhodesmas\nUI Button Press -- el_boss\nCancel or No Button Sound -- el_boss", {150, 800}, 70.0f, 2.0f, LIGHTGRAY);
}

void Game::drawPanel() {
    DrawTextEx(font, "Next Block", {width + 50, 0}, 75.0f, 2.0f, BLACK);
    DrawRectangle(width + 50, 75, size * 5, size * 5, BLACK);
    DrawTextEx(font, "Score", {width + 50, 500}, 75.0f, 2.0f, BLACK);
    DrawTextEx(font, scoreString, {width + 50, 575}, 75.0f, 2.0f, RED);
    DrawTextEx(font, "High Score", {width + 50, 700}, 75.0f, 2.0f, BLACK);
    DrawTextEx(font, highScoreString, {width + 50, 775}, 75.0f, 2.0f, RED);
    DrawTextEx(font, "Rows Cleared", {width + 50, 900}, 75.0f, 2.0f, BLACK);
    DrawTextEx(font, rowsClearedString, {width + 50, 975}, 75.0f, 2.0f, RED);
    DrawRectangle(width + 50, 1050, size * 6.5, size * 4.5, BLACK);
    DrawTextEx(font, "Controls", {width + 60, 1055}, 75.0f, 2.0f, RED);
    DrawTextEx(font, "Move: A, S, D, Arrows", {width + 60, 1125}, 50.0f, 2.0f, LIGHTGRAY);
    DrawTextEx(font, "Rotate Left: W, Up, O", {width + 60, 1200}, 50.0f, 2.0f, LIGHTGRAY);
    DrawTextEx(font, "Rotate Right: P", {width + 60, 1275}, 50.0f, 2.0f, LIGHTGRAY);
    DrawTextEx(font, "Pause: Backspace", {width + 60, 1350}, 50.0f, 2.0f, LIGHTGRAY);
    DrawTextEx(font, fpsString, {width + 500, 0}, 75.0f, 2.0f, RED);
}

void Game::drawNextBlock() {
    panelBlock->position.x = width + 50 + (size * 5 - (panelBlock->dimensions * size)) / 2;
    panelBlock->position.y = 75 + (size * 5 - (panelBlock->dimensions * size)) / 2;
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
        
        if (!speedIncreased) {
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

void Game::getNextBlock(int& type) {
    if (blocks.empty()) {
        blocks = {0, 1, 2, 3, 4, 5, 6};
    }

    int index = GetRandomValue(0, blocks.size() - 1);

    type = blocks.at(index);

    blocks.erase(blocks.begin() + index);
}

void Game::firstBlock() {
    getNextBlock(blockBag);
    blockType = blockBag;
    switch (blockType) {
        case 0:
            currentBlock = std::make_unique<OBlock>();
        break;
        case 1:
            currentBlock = std::make_unique<IBlock>();
        break;
        case 2:
            currentBlock = std::make_unique<SBlock>();
        break;
        case 3:
            currentBlock = std::make_unique<ZBlock>();
        break;
        case 4:
            currentBlock = std::make_unique<LBlock>();
        break;
        case 5:
            currentBlock = std::make_unique<JBlock>();
        break;
        case 6:
            currentBlock = std::make_unique<TBlock>();
        break;
    }

    getNextBlock(blockBag);
    nextBlockType = blockBag;
    switch (nextBlockType) {
        case 0:
            nextBlock = std::make_unique<OBlock>();
        break;
        case 1:
            nextBlock = std::make_unique<IBlock>();
        break;
        case 2:
            nextBlock = std::make_unique<SBlock>();
        break;
        case 3:
            nextBlock = std::make_unique<ZBlock>();
        break;
        case 4:
            nextBlock = std::make_unique<LBlock>();
        break;
        case 5:
            nextBlock = std::make_unique<JBlock>();
        break;
        case 6:
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
        case 0:
            nextBlock = std::make_unique<OBlock>();
        break;
        case 1:
            nextBlock = std::make_unique<IBlock>();
        break;
        case 2:
            nextBlock = std::make_unique<SBlock>();
        break;
        case 3:
            nextBlock = std::make_unique<ZBlock>();
        break;
        case 4:
            nextBlock = std::make_unique<LBlock>();
        break;
        case 5:
            nextBlock = std::make_unique<JBlock>();
        break;
        case 6:
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
    if (rowsCleared / speed == 10 && speed < 11 && !speedIncreased) {
        downInterval -= 0.05;
        scoreMultiplier += 0.05;
        speed++;
        speedIncreased = true;
        PlaySound(speedIncreaseSound);
    }
}