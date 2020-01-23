#include "raylib.h"
#include "game.h"
#include "player.h"

#define max(a, b) ((a)>(b)? (a) : (b))
#define min(a, b) ((a)<(b)? (a) : (b))

int main(void) {
    // enable config flags for resizable window and vertical synchro
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(GAME_WIDTH, GAME_HEIGHT, "rlneko");
    SetWindowMinSize(320, 240);

    // render texture initialization, used to hold the rendering result so we can easily resize it
    RenderTexture2D target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);
    SetTextureFilter(target.texture, FILTER_POINT);  // texture scale filter to use
    SetTargetFPS(GAME_FPS);

    Player player = LoadPlayer("resources/tora.png");

    while (!WindowShouldClose()) {
        float scale = min((float)GetScreenWidth()/GAME_WIDTH, (float)GetScreenHeight()/GAME_HEIGHT);

        UpdatePlayer(&player);

        BeginDrawing();
            ClearBackground(BLACK);

            BeginTextureMode(target);
                ClearBackground(RAYWHITE);
                DrawPlayer(&player);
            EndTextureMode();

            // draw RenderTexture2D to window, properly scaled
            DrawTexturePro(
                target.texture,
                (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
                (Rectangle) {
                    (GetScreenWidth() - ((float)GAME_WIDTH*scale)) * 0.5,
                    (GetScreenHeight() - ((float)GAME_HEIGHT*scale)) * 0.5,
                    (float)GAME_WIDTH * scale, (float)GAME_HEIGHT * scale
                },
                (Vector2){ 0, 0 },
                0.0f, WHITE
            );

        EndDrawing();
    }

    UnloadPlayer(&player);
    CloseWindow();

    return 0;
}