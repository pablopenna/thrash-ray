#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

#define PLAYER_ANIM_IDLE 0
#define PLAYER_MAX_ANIM 1

extern Entity player;

void playerInit();
void playerUpdate(Entity *player, float delta);
void playerDraw(Entity *player);

#endif
