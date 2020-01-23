#include "raylib.h"
#include "player.h"
#include "game.h"
#include "config.h"

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(GAME_WIDTH, GAME_HEIGHT, "rlneko");
    SetWindowMinSize(GAME_WIDTH, GAME_HEIGHT);
    SetTargetFPS(GAME_FPS);
    GameConfig gameConfig = { GAME_WIDTH, GAME_HEIGHT, GAME_FPS };
    PlayerConfig playerConfig = { PLAYER_TEXTURE_PATH, PLAYER_DROP_BOX, PLAYER_FPS, PLAYER_NUM_FRAMES };
    Game game = LoadGame(gameConfig, playerConfig);

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