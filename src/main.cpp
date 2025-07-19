#include "include/consts.h"
#include "include/arena.h"
#include "include/block.h"
#include "include/tetros.h"
#include "include/game.h"

void resizeWindow() {
    int monitor = GetCurrentMonitor();
    int monitorHeight = GetMonitorHeight(monitor);

    if (monitorHeight <= 1440) {
        windowScale = 0.75;
        if (monitorHeight <= 1080) {
            windowScale = 0.55;
        }

        CloseWindow();

        height *= windowScale;
        width = height / 2;
        size = width / 10;

        InitWindow(width * 1.75, height, "Game");
    }
}

int main() {
    //Initialize window
    InitWindow(width * 1.75, height, "Game");
    resizeWindow();
    InitAudioDevice();
    SetTargetFPS(60);

    Game game;

    game.loadAssets();
    PlayMusicStream(game.music);

    //Game loop
    while(!game.exitWindow) {
        UpdateMusicStream(game.music);

        //Draw
        BeginDrawing();
            ClearBackground(GRAY);

            //Game logic
            game.run();

        EndDrawing();
    }

    StopMusicStream(game.music);
    game.unloadAssets();

    //Close the game
    CloseAudioDevice();
    CloseWindow();

    return 0;
}