#include "stdlib.h"
#include "raylib.h"
#include "player.h"

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
    { 0.0f, 0.0f },  // UPTOGI
};

Player LoadPlayer(PlayerConfig config) {
    // we can only support the number of sequences that we have mappings for
    size_t numSequences = sizeof(sequenceToVelocityMap)/sizeof(sequenceToVelocityMap[0]);

    Texture2D texture = LoadTexture(config.texturePath);

    Rectangle frameRec = { 
        0.0f, 0.0f,
        (float)(texture.width / config.numFrames),
        (float)(texture.height / numSequences),
    };

    // drop player in the center of the area defined by config.dropBox
    Vector2 position = {
        (float)((config.dropBox.x + config.dropBox.width)/2 - frameRec.width/2),
        (float)((config.dropBox.y + config.dropBox.height)/2 - frameRec.height/2),
    };

    Vector2 velocity = { 0.0f, 0.0f };

    int framesCounter = 0;
    int currentFrame = 0;
    int currentSequence = AWAKE;

    return (Player) {
        config, texture, frameRec,
        position, velocity,
        framesCounter, currentFrame, currentSequence,
    };
};

PlayerSequence GetNextPlayerSequence(Player *player) {
    if (IsKeyDown(KEY_Z)) {
        return JARE;
    } else if (IsKeyDown(KEY_A)) {
        return KAKI;
    } else if (IsKeyDown(KEY_X)) {
        return MATI;
    } else if (IsKeyDown(KEY_S)) {
        return SLEEP;
    } else if (IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_SPACE)) {
        return DTOGI;
    } else if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_SPACE)) {
        return LTOGI;
    } else if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_SPACE)) {
        return RTOGI;
    } else if (IsKeyDown(KEY_UP) && IsKeyDown(KEY_SPACE)) {
        return UPTOGI;
    } else if (IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_LEFT)) {
        return DWLEFT;
    } else if (IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_RIGHT)) {
        return DWRIGHT;
    } else if (IsKeyDown(KEY_UP) && IsKeyDown(KEY_LEFT)) {
        return UPLEFT;
    } else if (IsKeyDown(KEY_UP) && IsKeyDown(KEY_RIGHT)) {
        return UPRIGHT;
    } else if (IsKeyDown(KEY_DOWN)) {
        return DOWN;
    } else if (IsKeyDown(KEY_LEFT)) {
        return LEFT;
    } else if (IsKeyDown(KEY_RIGHT)) {
        return RIGHT;
    } else if (IsKeyDown(KEY_UP)) {
        return UP;
    } else {
        return AWAKE;
    }
}

void AnimatePlayer(Player *player) {
    player->currentFrame++;

    if (player->currentFrame > player->config.numFrames - 1) player->currentFrame = 0;

    player->frameRec.x = (float)(player->currentFrame * player->frameRec.width);
    player->frameRec.y = (float)(player->currentSequence * player->frameRec.height);
}

void UpdatePlayer(Player *player) {
    player->framesCounter++;
    player->currentSequence = GetNextPlayerSequence(player);

    player->velocity = sequenceToVelocityMap[player->currentSequence];
    player->position.x += player->velocity.x;
    player->position.y += player->velocity.y;
};

void DrawPlayer(Player *player) {
    DrawTextureRec(player->texture, player->frameRec, player->position, WHITE);
}

void UnloadPlayer(Player *player) {
    UnloadTexture(player->texture);
};