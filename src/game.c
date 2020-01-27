#include <stdlib.h>
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
        (Vector2){
            player.position.x + player.frameRec.width/2,
            player.position.y + player.frameRec.height/2,
        },
        0.0f, 1.0f, cameraConfig
    };

    Terrain terrain = LoadTerrain(terrainConfig);

    SetTextureFilter(target.texture, FILTER_POINT);  // texture scale filter to use

    return (Game){ gameConfig, target, player, camera, terrain };
}

void UpdateGame(Game *game) { 
    UpdatePlayer(&game->player);
    UpdateSmoothFollowCamera(&game->camera, (Vector2){
        game->player.position.x + game->player.frameRec.width/2,
        game->player.position.y + game->player.frameRec.height/2
    });

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
}

void UnloadGame(Game *game) {
    UnloadPlayer(&game->player);
    UnloadTerrain(&game->terrain);
}