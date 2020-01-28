#include <raylib.h>
#include "startscreen.h"
#include "player.h"
#include "terrain.h"
#include "game.h"
#include "config.h"

#define max(a, b) ((a)>(b)? (a) : (b))
#define min(a, b) ((a)<(b)? (a) : (b))

typedef enum { STARTSCREEN, GAME } Screen;

int main(void) {
    Game game;
    PlayerConfig playerConfig;
    RenderTexture2D *target;
    float scale;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(GAME_WIDTH, GAME_HEIGHT, "rlneko");
    SetWindowMinSize(GAME_WIDTH, GAME_HEIGHT);
    SetTargetFPS(GAME_FPS);

    StartScreenConfig startConfig = { "resources/characters.png", GAME_WIDTH, GAME_HEIGHT, STARTSCREEN_NUM_CHARACTERS };
    SmoothFollowCameraConfig cameraConfig = { CAMERA_MIN_SPEED, CAMERA_MIN_EFFECT_LENGTH, CAMERA_FRACTION_SPEED };
    TerrainConfig terrainConfig = { GAME_WIDTH, GAME_HEIGHT };
    GameConfig gameConfig = { GAME_WIDTH, GAME_HEIGHT, GAME_FPS };

    StartScreen start = LoadStartScreen(startConfig);
    RenderTexture2D *screenToTargetMap[2] = { &start.target, &game.target };
    Screen currentScreen = STARTSCREEN;

    while (!WindowShouldClose()) {
        switch (currentScreen) {
            case STARTSCREEN:
                UpdateStartScreen(&start);
                if (start.enter) {
                    playerConfig = (PlayerConfig){ GetCharacterTexturePath(&start), PLAYER_DROP_BOX, PLAYER_FPS, PLAYER_NUM_FRAMES };
                    game = LoadGame(gameConfig, playerConfig, cameraConfig, terrainConfig);
                    currentScreen = GAME;
                }
                break;
            case GAME:
                UpdateGame(&game);
                break;
        }

        target = screenToTargetMap[currentScreen];
        scale = min((float)GetScreenWidth()/target->texture.width, (float)GetScreenHeight()/target->texture.height);

        BeginDrawing();
            ClearBackground(BLACK);

            // draw to RenderTexture2D
            BeginTextureMode(*target);
                switch (currentScreen) {
                    case STARTSCREEN:
                        DrawStartScreen(&start);
                        break;
                    case GAME:
                        DrawGame(&game);
                        break;
                }
            EndTextureMode();

            // draw RenderTexture2D to window, properly scaled
            DrawTexturePro(
                target->texture,
                (Rectangle){ 0.0f, 0.0f, (float)target->texture.width, (float)-target->texture.height },
                (Rectangle) {
                    (GetScreenWidth() - ((float)target->texture.width * scale)) * 0.5,
                    (GetScreenHeight() - ((float)target->texture.height * scale)) * 0.5,
                    (float)target->texture.width * scale, (float)target->texture.height * scale
                },
                (Vector2){ 0, 0 },
                0.0f, WHITE
            );
        EndDrawing();
    }

    UnloadGame(&game);
    CloseWindow();

    return 0;
}