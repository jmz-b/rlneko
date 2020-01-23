#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "player.h"

#define GAME_WIDTH 400
#define GAME_HEIGHT 300
#define GAME_FPS 60

typedef struct {
    RenderTexture2D target;
    Player player;

    int width;
    int height;
    int FPS;
    float scale;
} Game;

Game LoadGame(int width, int height, int FPS);
void UpdateGame(Game *game);
void DrawGame(Game *game);
void UnloadGame(Game *game);

#endif