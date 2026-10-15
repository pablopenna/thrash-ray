#ifndef ENTITY_PLAYER_SHOT_H
#define ENTITY_PLAYER_SHOT_H

#include "entity.h"

struct PlayerShot {
    Vector2 *projectilePoints; // array
    int pointCount;
    float duration;
    float timer;
    bool isActive;
};

PlayerShot* getPlayerShot();

void onPlayerShot(Entity* player, PlayerShot* shot);
void playerShotUpdate(float delta);
void playerShotDraw();

#endif
