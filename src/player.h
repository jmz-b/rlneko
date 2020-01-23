#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

#define PLAYER_NUM_FRAMES 2
#define PLAYER_NUM_SEQUENCES 17

typedef enum {
    AWAKE, DOWN, DTOGI, DWLEFT, DWRIGHT, JARE, KAKI, LEFT, LTOGI, MATI,
    RIGHT, RTOGI, SLEEP, UP, UPLEFT, UPRIGHT, UPTOGI
} PlayerSequence;

typedef struct Player {
    Texture2D texture;
    Rectangle frameRec;
    Vector2 position;
    Vector2 velocity;
    int FPS;

    int framesCounter;
    int currentFrame;
    int currentSequence;
} Player;

Player LoadPlayer(const char *path, int gameWidth, int gameHeight);
PlayerSequence GetNextPlayerSequence(Player *player);
void AnimatePlayer(Player *player, int gameFPS);
void UpdatePlayer(Player *player, int gameFPS);
void DrawPlayer(Player *player);
void UnloadPlayer(Player *player);

#endif