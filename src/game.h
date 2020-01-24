#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include "player.h"

typedef struct {
    int width;
    int height;
    int FPS;
} GameConfig;

typedef struct {
    GameConfig config;
    RenderTexture2D target;
    Player player;
} Game;

Game LoadGame(GameConfig gameConfig, PlayerConfig playerConfig);
void UpdateGame(Game *game);
void DrawGame(Game *game);
void UnloadGame(Game *game);

#endif