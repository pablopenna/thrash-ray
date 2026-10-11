#ifndef FLOOR_H
#define FLOOR_H

#include "entity/entity.h"
#include "raylib.h"

#define MIN_FLOOR_TILES 2
#define MAX_FLOOR_TILES 20

#define FLOOR_TILE_WIDTH 40
#define FLOOR_TILE_HEIGHT 20

typedef struct {
    Rectangle rectangle;
    char isActive;
} FloorTile;


int getNumberOfFloorTiles();
FloorTile* getFloorTileAt(int index);

void floorInit();
void floorUpdate();
void floorDraw();

bool isEntityUnderFloor(Entity* entity);

#endif
