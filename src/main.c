#include "raylib.h"
#include "game.h"

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(GAME_WIDTH, GAME_HEIGHT, "rlneko");
    SetWindowMinSize(GAME_WIDTH, GAME_HEIGHT);
    SetTargetFPS(GAME_FPS);
    Game game = LoadGame(GAME_WIDTH, GAME_HEIGHT, GAME_FPS);

    while (!WindowShouldClose()) {
        UpdateGame(&game);
        BeginDrawing();
            DrawGame(&game);
        EndDrawing();
    }

    UnloadGame(&game);
    CloseWindow();

    return 0;
}