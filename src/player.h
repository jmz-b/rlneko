#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

#define PLAYER_NUM_SEQUENCES 17

typedef enum {
    AWAKE, DOWN, DTOGI, DWLEFT, DWRIGHT, JARE, KAKI, LEFT, LTOGI, MATI,
    RIGHT, RTOGI, SLEEP, UP, UPLEFT, UPRIGHT, UPTOGI
} PlayerSequence;

typedef struct {
    const char *texturePath;
    Rectangle dropBox;
    int FPS;
    int numFrames;
} PlayerConfig;

typedef struct {
    PlayerConfig config;
    Texture2D texture;
    Rectangle frameRec;
    Vector2 position;
    Vector2 velocity;
    int framesCounter;
    int currentFrame;
    int currentSequence;
} Player;

Player LoadPlayer(PlayerConfig config);
PlayerSequence GetNextPlayerSequence(Player *player);
void AnimatePlayer(Player *player);
void UpdatePlayer(Player *player);
void DrawPlayer(Player *player);
void UnloadPlayer(Player *player);

#endif