#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

extern Entity player;

void playerInit(EntityRegistry *registry);
void playerUpdate(Entity *player, float delta);
void playerDraw(Entity *player);

#endif
