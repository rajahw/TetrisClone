#include "include/consts.h"
#include "include/arena.h"
#include "include/block.h"
#include "include/tetros.h"
#include "include/game.h"

int main() {
    //Initialize window
    InitWindow(width * 1.75, height, "Tetris");
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