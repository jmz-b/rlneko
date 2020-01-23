#include "raylib.h"
#include "game.h"
#include "player.h"

int main(void) {
    InitWindow(GAME_WIDTH, GAME_HEIGHT, "rlneko");
    SetTargetFPS(GAME_FPS);

    Player player = LoadPlayer("resources/tora.png");

    while (!WindowShouldClose()) {
        UpdatePlayer(&player);

        BeginDrawing();
            ClearBackground(LIGHTGRAY);
            DrawPlayer(&player);
        EndDrawing();
    }

    UnloadPlayer(&player);
    CloseWindow();

    return 0;
}