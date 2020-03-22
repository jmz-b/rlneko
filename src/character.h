#ifndef CHARACTER_H
#define CHARACTER_H

#include <raylib.h>

#define CHARACTER_NUM_SEQUENCES 17

typedef enum { NEKO, DOG, TORA, SAKURA, TOMOYO, BEASTIE } CharacterName;

typedef enum {
    AWAKE, DOWN, DTOGI, DWLEFT, DWRIGHT, JARE, KAKI, LEFT, LTOGI, MATI,
    RIGHT, RTOGI, SLEEP, UP, UPLEFT, UPRIGHT, UPTOGI
} CharacterSequence;

typedef struct {
    const char *texturePath;
    Rectangle dropRec;
    int FPS;
    int numFrames;
} CharacterConfig;

typedef struct {
    CharacterConfig config;
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
} Character;

Character LoadCharacter(CharacterConfig config);
const char *GetCharacterTexturePath(CharacterName name);
void AnimateCharacter(Character *character);
void DrawCharacter(Character *character);
void UnloadCharacter(Character *character);

#endif