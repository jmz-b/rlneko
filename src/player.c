#include <stdlib.h>
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include "character.h"
#include "config.h"

static const Vector2 sequenceToVelocityMap[CHARACTER_NUM_SEQUENCES] = {
    { 0.0f, 0.0f },  // AWAKE
    { 0.0f, 1.0f },  // DOWN
    { 0.0f, 0.0f },  // DTOGI
    { -1.0f, 1.0f },  // DWLEFT
    { 1.0f, 1.0f },  // DWRIGHT
    { 0.0f, 0.0f },  // JARE
    { 0.0f, 0.0f },  // KAKI
    { -1.0f, 0.0f },  // LEFT
    { 0.0f, 0.0f },  // LTOGI
    { 0.0f, 0.0f },  // MATI
    { 1.0f, 0.0f },  // RIGHT
    { 0.0f, 0.0f },  // RTOGI
    { 0.0f, 0.0f },  // SLEEPY
    { 0.0f, -1.0f },  // UP
    { -1.0f, -1.0f },  // UPLEFT
    { 1.0f, -1.0f },  // UPRIGHT
    { 0.0f, 0.0f }  // UPTOGI
};

CharacterSequence GetNextPlayerSequence(Character *character, Vector2 targetPosition) {
    // normalized displacement from click
    const Vector2 targetDisplacement = Vector2Normalize(Vector2Subtract(targetPosition, character->position));
    const float rotation = atan2f(targetDisplacement.x, targetDisplacement.y);

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(targetPosition, character->bbox)) return KAKI;

    if (rotation == 0.0f) return DOWN;
    else if (rotation == PI/2.0f) return RIGHT;
    else if (rotation == -PI/2.0f) return LEFT;
    else if (rotation == PI) return UP;
    else if (rotation > 0.0f && rotation < PI/2.0f) return DWRIGHT;
    else if (rotation < 0.0f && rotation > -PI/2.0f) return DWLEFT;
    else if (rotation > PI/2.0f && rotation < PI) return UPRIGHT;
    else if (rotation < -PI/2.0f && rotation > -PI) return UPLEFT;

    if (character->sleepTimer > 60 * 10)  return SLEEP;
    else if (character->sleepTimer > 60 * 6) return MATI;
    else if (character->sleepTimer > 60 * 2) return JARE;

    return AWAKE;
}

void UpdatePlayer(Character *character, Vector2 targetPosition) {
    character->sleepTimer++;
    character->framesCounter++;

    character->currentSequence = GetNextPlayerSequence(character, targetPosition);
    character->velocity = sequenceToVelocityMap[character->currentSequence];

    if (character->velocity.x != 0.0f || character->velocity.y != 0.0f) {
        character->sleepTimer = 0.0f;
        character->position = Vector2Add(character->position, character->velocity);
        character->bbox.x = character->position.x - character->frameRec.width/2;
        character->bbox.y = character->position.y - character->frameRec.height/2;
    }
};