
#ifndef NPC_H
#define NPC_H

#include <raylib.h>

#define NPC_NUM_SEQUENCES 17

typedef enum {
    AWAKE, DOWN, DTOGI, DWLEFT, DWRIGHT, JARE, KAKI, LEFT, LTOGI, MATI,
    RIGHT, RTOGI, SLEEP, UP, UPLEFT, UPRIGHT, UPTOGI
} NPCSequence;

typedef struct {
    const char *texturePath;
    Rectangle dropRec;
    int FPS;
    int numFrames;
} NPCConfig;

typedef struct {
    NPCConfig config;
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
} NPC;

NPC LoadNPC(NPCConfig config);
NPCSequence GetNextNPCSequence(NPC *npc, Vector2 targetPosition);
void AnimateNPC(NPC *npc);
void UpdateNPC(NPC *npc, Vector2 targetPosition);
void DrawNPC(NPC *npc);
void UnloadNPC(NPC *npc);

#endif