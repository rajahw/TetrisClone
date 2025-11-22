#pragma once
#include "consts.h"
#include "tetros.h"
#include "block.h"
#include "arena.h"

class Game {
    public:
        Arena arena;
        Arena grayOut;
        BlockEnum blockType;
        BlockEnum nextBlockType;
        BlockEnum blockBag;
        int numCleared;
        int rowsCleared;
        int levelCleared;
        int score;
        int highScore;
        int speed;
        int fps;
        char fpsString[16];
        char scoreString[16];
        char highScoreString[16];
        char rowsClearedString[16];
        bool blockMoving;
        bool locking;
        bool exitWindow;
        bool gameOver;
        bool paused;
        bool speedIncreased;
        bool grayOutUpdated;
        bool loseSoundPlayed;
        std::vector<BlockEnum> blocks;
        std::unique_ptr<Block> currentBlock;
        std::unique_ptr<Block> nextBlock;
        std::unique_ptr<Block> panelBlock;
        Vector2 mouseLocation;
        Font font;
        Music music;
        Sound loseSound;
        Sound openMenu;
        Sound selectMenu;
        Sound scoreSound;
        Sound speedIncreaseSound;
        Color gameOverScreen = {0, 0, 0, 200};
        Rectangle yesHitbox = {130.0f * windowScale, 900.0f * windowScale, 220.0f * windowScale, 90.0f * windowScale};
        Rectangle noHitbox = {130.0f * windowScale, 1000.0f * windowScale, 160.0f * windowScale, 90.0f * windowScale};

        Game();
        void run();
        void reset();
        void loadAssets();
        void unloadAssets();
        void moveInput(const std::unique_ptr<Block>&);
        void rotateInput(const std::unique_ptr<Block>&);
        void updateArena();
        void updateGrayOut();
        void drawGameOver();
        void drawPause();
        void drawPanel();
        void drawNextBlock();
        void updatePanel();
        bool rowFull(int);
        void clearRows();
        bool gameIsOver();
        void getNextBlock(BlockEnum&);
        void firstBlock();
        void spawnBlock();
        bool timePassed(double, double&);
        void increaseSpeed();
};