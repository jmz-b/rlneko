#include <stdlib.h>
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include "character.h"
#include "config.h"

Character LoadCharacter(CharacterConfig config) {
    Texture2D texture = LoadTexture(config.texturePath);

    Rectangle frameRec = { 
        0.0f, 0.0f,
        (float)texture.width / config.numFrames,
        (float)texture.height / CHARACTER_NUM_SEQUENCES
    };

    // drop character in the center of the area defined by config.dropRec
    Vector2 position = {
        (float)(config.dropRec.x + config.dropRec.width)/2,
        (float)(config.dropRec.y + config.dropRec.height)/2
    };

    Rectangle bbox = (Rectangle){
        position.x - frameRec.width/2,
        position.y - frameRec.height/2,
        frameRec.width, frameRec.height
    };

    Vector2 velocity = { 0.0f, 0.0f };
    int sleepTimer = 0;
    int clickTimer = 0;
    int framesCounter = 0;
    int currentFrame = 0;
    int currentSequence = AWAKE;

    return (Character){
        config, texture, frameRec, position, bbox, velocity,
        sleepTimer, clickTimer,
        framesCounter, currentFrame, currentSequence
    };
};

const char *GetCharacterTexturePath(CharacterName name) {
    switch (name) {
        case NEKO: return "resources/neko.png";
        case DOG: return "resources/dog.png";
        case TORA: return "resources/tora.png";
        case SAKURA: return "resources/sakura.png";
        case TOMOYO: return "resources/tomoyo.png";
        case BEASTIE: return "resources/beastie.png";
        default: return "resources/neko.png";
    };
}

void AnimateCharacter(Character *character) {
    character->currentFrame++;

    if (character->currentFrame > character->config.numFrames - 1) character->currentFrame = 0;

    character->frameRec.x = (float)character->currentFrame * (float)character->frameRec.width;
    character->frameRec.y = (float)character->currentSequence * (float)character->frameRec.height;
}

void DrawCharacter(Character *character) {
    DrawTextureRec(
        character->texture,
        character->frameRec,
        Vector2Subtract(character->position, (Vector2){ character->frameRec.width/2, character->frameRec.height/2 }),
        WHITE
    );
}

void UnloadCharacter(Character *character) {
    UnloadTexture(character->texture);
};