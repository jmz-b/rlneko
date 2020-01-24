#ifndef CHARACTER_SELECT_H
#define CHARACTER_SELECT_H

#include <raylib.h>

typedef enum { NEKO, DOG, TORA, SAKURA, TOMOYO, BEASTIE } CharacterTexture;

typedef struct {
    const char *texturePath;
    int width;
    int height;
    int numCharacters;
} StartScreenConfig;

typedef struct {
    StartScreenConfig config;
    RenderTexture2D target;
    Texture2D characterSelectTexture;
    CharacterTexture selectedCharacter;
    bool enter;
} StartScreen;

StartScreen LoadStartScreen(StartScreenConfig config);
const char *GetCharacterTexturePath(StartScreen *start);
void UpdateStartScreen(StartScreen *intro);
void DrawStartScreen(StartScreen *intro);

#endif