#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

#define PLAYER_NUM_SEQUENCES 17

typedef enum {
    AWAKE, DOWN, DTOGI, DWLEFT, DWRIGHT, JARE, KAKI, LEFT, LTOGI, MATI,
    RIGHT, RTOGI, SLEEP, UP, UPLEFT, UPRIGHT, UPTOGI
} PlayerSequence;

typedef struct {
    const char *texturePath;
    Rectangle dropRec;
    int FPS;
    int numFrames;
} PlayerConfig;

typedef struct {
    PlayerConfig config;
    Texture2D texture;
    Rectangle frameRec;
    Vector2 position;
    Rectangle bbox;
    Vector2 velocity;
    int sleepTimer;
    int clickTimer;
    int framesCounter;
    int currentFrame;
    int currentSequence;
} Player;

Player LoadPlayer(PlayerConfig config);
PlayerSequence GetNextPlayerSequence(Player *player, Vector2 targetPosition);
void AnimatePlayer(Player *player);
void UpdatePlayer(Player *player, Vector2 targetPosition);
void DrawPlayer(Player *player);
void UnloadPlayer(Player *player);

#endif