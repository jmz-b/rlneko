#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "character.h"

void UpdatePlayer(Character *player, Vector2 targetPosition);
CharacterSequence GetNextPlayerSequence(CharacterSequence *player, Vector2 targetPosition);

#endif