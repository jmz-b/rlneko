#include <string.h>
#include <raylib.h>
#include "startscreen.h"

StartScreen LoadStartScreen(StartScreenConfig config) {
    RenderTexture2D target = LoadRenderTexture(config.width, config.height);
    Texture2D characterSelectTexture = LoadTexture(config.texturePath);
    CharacterName selectedCharacter = NEKO;
    bool enter = false;

    SetTextureFilter(target.texture, FILTER_POINT);  // texture scale filter to use

    return (StartScreen){ config, target, characterSelectTexture, selectedCharacter, enter };
}

void UpdateStartScreen(StartScreen *start) {
    if (IsKeyPressed(KEY_LEFT) && start->selectedCharacter > 0) start->selectedCharacter--;
    else if (IsKeyPressed(KEY_RIGHT) && start->selectedCharacter < start->config.numCharacters - 1) start->selectedCharacter++;
    else if (IsKeyPressed(KEY_ENTER)) start->enter = true;
}

void DrawStartScreen(StartScreen *start) {
    const char *text = "press [Enter] to start";
    const int fontSize = 10;
    const int selectWidth = start->characterSelectTexture.width/start->config.numCharacters;
    const int texturePosX = start->config.width/2 - start->characterSelectTexture.width/2;
    const int texturePosY = start->config.height/2 - start->characterSelectTexture.height;
    const int textPosX = start->config.width/2 - (strlen(text) * fontSize)/4; 
    const int textPosY = start->config.height/2 + start->characterSelectTexture.height;

    ClearBackground(LIGHTGRAY);
    DrawTexture(start->characterSelectTexture, texturePosX, texturePosY, WHITE);
    DrawRectangleLines(texturePosX + start->selectedCharacter * selectWidth, texturePosY, selectWidth, selectWidth, BLACK);
    DrawText(text, textPosX, textPosY, fontSize, BLACK);
}