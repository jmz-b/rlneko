#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include "character.h"
#include "camera.h"
#include "terrain.h"

typedef struct {
    int width;
    int height;
    int FPS;
} GameConfig;

typedef struct {
    GameConfig config;
    RenderTexture2D target;
    Character player;
    SmoothFollowCamera camera;
    Terrain terrain;
    Vector2 clickPosition;
} Game;

Game LoadGame(GameConfig gameConfig, CharacterConfig playerConfig, SmoothFollowCameraConfig cameraConfig, TerrainConfig terrainConfig);
void UpdateGame(Game *game);
void DrawGame(Game *game);
void UnloadGame(Game *game);

#endif