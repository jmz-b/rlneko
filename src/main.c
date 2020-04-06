#include <raylib.h>
#include "startscreen.h"
#include "character.h"
#include "player.h"
#include "terrain.h"
#include "game.h"
#include "config.h"

#define max(a, b) ((a)>(b)? (a) : (b))
#define min(a, b) ((a)<(b)? (a) : (b))

typedef enum { STARTSCREEN, GAME } Screen;

int main(void) {
    Game game;
    CharacterConfig playerConfig;
    RenderTexture2D *target;
    // float scaleX;
    // float scaleY;
    // float drawScale;

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

        // select screen
        switch (currentScreen) {
            case STARTSCREEN:
                UpdateStartScreen(&start);
                if (start.enter) {
                    playerConfig = (CharacterConfig){ GetCharacterTexturePath(start.selectedCharacter), PLAYER_DROP_BOX, PLAYER_FPS, PLAYER_NUM_FRAMES };
                    game = LoadGame(gameConfig, playerConfig, cameraConfig, terrainConfig);
                    currentScreen = GAME;
                }
                break;
            case GAME:
                UpdateGame(&game);
                break;
        }

        // get current RenderTexture2D target
        target = screenToTargetMap[currentScreen];

        // get scale factors
        // scaleX = (float)GetScreenWidth()/target->texture.width;
        // scaleY = (float)GetScreenHeight()/target->texture.height;
        // drawScale = min(scaleX, scaleY);

        // scale mouse coords
        // SetMouseScale(1.0f/scaleX, 1.0f/scaleY);

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
                    (GetScreenWidth() - ((float)target->texture.width * 1)) * 0.5,
                    (GetScreenHeight() - ((float)target->texture.height * 1)) * 0.5,
                    (float)target->texture.width * 1, (float)target->texture.height * 1
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