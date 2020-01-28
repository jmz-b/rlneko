#include <stdlib.h>
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include "player.h"
#include "config.h"

static const Vector2 sequenceToVelocityMap[PLAYER_NUM_SEQUENCES] = {
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

Player LoadPlayer(PlayerConfig config) {
    // we can only support the number of sequences that we have mappings for
    size_t numSequences = sizeof(sequenceToVelocityMap)/sizeof(sequenceToVelocityMap[0]);

    Texture2D texture = LoadTexture(config.texturePath);

    Rectangle frameRec = { 
        0.0f, 0.0f,
        (float)texture.width / config.numFrames,
        (float)texture.height / numSequences
    };

    // drop player in the center of the area defined by config.dropRec
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

    return (Player){
        config, texture, frameRec, position, bbox, velocity,
        sleepTimer, clickTimer,
        framesCounter, currentFrame, currentSequence
    };
};

PlayerSequence GetNextPlayerSequence(Player *player, Vector2 targetPosition) {
    // normalized displacement from click
    Vector2 targetDisplacement = Vector2Normalize(Vector2Subtract(targetPosition, player->position));
    float rotation = atan2f(targetDisplacement.x, targetDisplacement.y);

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(targetPosition, player->bbox)) return KAKI;

    if (rotation == 0.0f) return DOWN;
    else if (rotation == PI/2.0f) return RIGHT;
    else if (rotation == -PI/2.0f) return LEFT;
    else if (rotation == PI) return UP;
    else if (rotation > 0.0f && rotation < PI/2.0f) return DWRIGHT;
    else if (rotation < 0.0f && rotation > -PI/2.0f) return DWLEFT;
    else if (rotation > PI/2.0f && rotation < PI) return UPRIGHT;
    else if (rotation < -PI/2.0f && rotation > -PI) return UPLEFT;

    if (player->sleepTimer > 60 * 10)  return SLEEP;
    else if (player->sleepTimer > 60 * 6) return MATI;
    else if (player->sleepTimer > 60 * 2) return JARE;

    return AWAKE;
}

void AnimatePlayer(Player *player) {
    player->currentFrame++;

    if (player->currentFrame > player->config.numFrames - 1) player->currentFrame = 0;

    player->frameRec.x = (float)player->currentFrame * (float)player->frameRec.width;
    player->frameRec.y = (float)player->currentSequence * (float)player->frameRec.height;
}

void UpdatePlayer(Player *player, Vector2 targetPosition) {
    player->sleepTimer++;
    player->framesCounter++;

    player->currentSequence = GetNextPlayerSequence(player, targetPosition);
    player->velocity = sequenceToVelocityMap[player->currentSequence];

    if (player->velocity.x != 0.0f || player->velocity.y != 0.0f) {
        player->sleepTimer = 0.0f;
        player->position = Vector2Add(player->position, player->velocity);
        player->bbox.x = player->position.x - player->frameRec.width/2;
        player->bbox.y = player->position.y - player->frameRec.height/2;
    }
};

void DrawPlayer(Player *player) {
    DrawTextureRec(
        player->texture,
        player->frameRec,
        Vector2Subtract(player->position, (Vector2){ player->frameRec.width/2, player->frameRec.height/2 }),
        WHITE
    );
}

void UnloadPlayer(Player *player) {
    UnloadTexture(player->texture);
};