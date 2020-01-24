#include <string.h>
#include <raylib.h>
#include "startscreen.h"

StartScreen LoadStartScreen(StartScreenConfig config) {
    RenderTexture2D target = LoadRenderTexture(config.width, config.height);
    Texture2D characterSelectTexture = LoadTexture(config.texturePath);
    CharacterTexture selectedCharacter = NEKO;
    bool enter = false;

    SetTextureFilter(target.texture, FILTER_POINT);  // texture scale filter to use

    return (StartScreen) { config, target, characterSelectTexture, selectedCharacter, enter };
}

const char *GetCharacterTexturePath(StartScreen *start) {
    switch (start->selectedCharacter) {
        case NEKO: return "resources/neko.png";
        case DOG: return "resources/dog.png";
        case TORA: return "resources/tora.png";
        case SAKURA: return "resources/sakura.png";
        case TOMOYO: return "resources/tomoyo.png";
        case BEASTIE: return "resources/beastie.png";
        default: return "resources/neko.png";
    };
}

void UpdateStartScreen(StartScreen *start) {
    if (IsKeyPressed(KEY_LEFT) && start->selectedCharacter > 0) start->selectedCharacter--;
    if (IsKeyPressed(KEY_RIGHT) && start->selectedCharacter < start->config.numCharacters - 1) start->selectedCharacter++;
    if (IsKeyPressed(KEY_ENTER)) start->enter = true;
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