#ifndef CHARACTER_SELECT_H
#define CHARACTER_SELECT_H

#include <raylib.h>
#include "character.h"

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
    CharacterName selectedCharacter;
    bool enter;
} StartScreen;

StartScreen LoadStartScreen(StartScreenConfig config);
void UpdateStartScreen(StartScreen *intro);
void DrawStartScreen(StartScreen *intro);

#endif