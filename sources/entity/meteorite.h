#ifndef METEORITE_H
#define METEORITE_H

#include "raylib.h"
#include "entity.h"

#define METEORITE_MAX_QUANTITY 512

#define METEORITE_ANIM_IDLE 0
#define METEORITE_ANIM_MOVE 1
#define METEORITE_MAX_ANIM 2

void meteoritesInit();
void meteoritesUpdateAll(float delta);
void meteoritesDrawAll();

Entity* setupNewMeteorite(Vector2 position, Vector2 direction);

#endif
