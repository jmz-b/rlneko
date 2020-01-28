#include <stdlib.h>
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include "player.h"
#include "camera.h"
#include "terrain.h"
#include "game.h"

Game LoadGame(GameConfig gameConfig, PlayerConfig playerConfig, SmoothFollowCameraConfig cameraConfig, TerrainConfig terrainConfig) {
    RenderTexture2D target = LoadRenderTexture(gameConfig.width, gameConfig.height);

    Player player = LoadPlayer(playerConfig);

    SmoothFollowCamera camera = {
        (Vector2){ gameConfig.width/2, gameConfig.height/2 },
        player.position,
        0.0f, 1.0f, cameraConfig
    };

    Terrain terrain = LoadTerrain(terrainConfig);

    SetTextureFilter(target.texture, FILTER_POINT);  // texture scale filter to use

    return (Game){ gameConfig, target, player, camera, terrain, player.position };
}

void UpdateGame(Game *game) { 
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        // get the player position and subtract the screen center vector from it
        // add the result to the mouse position
        // this gets the target click position relative to the player
        game->clickPosition = Vector2Add(
            GetMousePosition(),
            Vector2Subtract(
                game->player.position,
                (Vector2){ (float)game->config.width/2, (float)game->config.height/2 }
            )
        );

        // round click position to account for reduced accuracy introduced by scaling and camera drift
        game->clickPosition.x = round(game->clickPosition.x);
        game->clickPosition.y = round(game->clickPosition.y);
    }

    UpdatePlayer(&game->player, game->clickPosition);

    UpdateSmoothFollowCamera(&game->camera, game->player.position);

    // step player animation every gameFPS/playerFPS cycles
    if (game->player.framesCounter >= game->config.FPS/game->player.config.FPS) {
        game->player.framesCounter = 0;
        AnimatePlayer(&game->player);
    };
}

void DrawGame(Game *game) {
    // get pointer to nested Camera2D structure
    Camera2D *camera2d = (Camera2D *)&game->camera;

    ClearBackground(LIGHTGRAY);

    BeginMode2D(*camera2d);
        DrawTexture(game->terrain.texture, 0, 0, WHITE);
        DrawPlayer(&game->player);
    EndMode2D();

    // DrawText(FormatText("clickPosition.x: %3.5f", game->clickPosition.x), 10, 10, 20, BLACK);
    // DrawText(FormatText("clickPosition.y: %3.5f", game->clickPosition.y), 10, 40, 20, BLACK);
}

void UnloadGame(Game *game) {
    UnloadPlayer(&game->player);
    UnloadTerrain(&game->terrain);
}