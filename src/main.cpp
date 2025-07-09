#include "consts.h"
#include "arena.h"
#include "block.h"
#include "tetros.h"
#include "game.h"

int main() {
    //Initialize window
    InitWindow(width + 600, height, "Tetris");
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