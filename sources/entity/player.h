#ifndef ENTITY_PLAYER_H
#define ENTITY_PLAYER_H

#include "entity.h"

#define PLAYER_ANIM_IDLE 0
#define PLAYER_MAX_ANIM 1

Entity* getPlayer();

void playerInit();
void playerUpdate(float delta);
void playerDraw();

#endif
