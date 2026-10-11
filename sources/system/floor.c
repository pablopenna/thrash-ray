#include "floor.h"

#include "raylib.h"
#include "utils/math.h"
#include <stdbool.h>

static FloorTile floorTiles[MAX_FLOOR_TILES];
static int numberOfFloorTiles = 0;
static int underFloorYCoord = 0; // y coordinate right below the floor

int getNumberOfFloorTiles() {
    return numberOfFloorTiles;
}

FloorTile* getFloorTileAt(int index) {
    return &floorTiles[index];
}

bool isEntityUnderFloor(Entity* entity) {
    return entity->position.y > underFloorYCoord;
}

FloorTile generateTileAt(int index, int yPos) {
    return (FloorTile) {
        .rectangle = (Rectangle){
            .x = index * FLOOR_TILE_WIDTH,
            .y = yPos,
            .width = FLOOR_TILE_WIDTH,
            .height = FLOOR_TILE_HEIGHT,
        },
        .isActive = true,
    };
}

void tileUpdate(FloorTile* tile) {

}

void drawTile(FloorTile* tile) {
    if(!tile->isActive) return;
    DrawRectangleRec(tile->rectangle, WHITE);
    DrawRectangleLinesEx(tile->rectangle, 1, DARKGRAY);
}

void floorInit() {
    numberOfFloorTiles = iClamp(GetScreenWidth()/FLOOR_TILE_WIDTH, MIN_FLOOR_TILES, MAX_FLOOR_TILES);
    int tileY = GetScreenHeight() - FLOOR_TILE_HEIGHT;
    underFloorYCoord = tileY + FLOOR_TILE_HEIGHT;

    for(int i=0; i<numberOfFloorTiles; i++) {
        floorTiles[i] = generateTileAt(i, tileY);
    }
}

void floorUpdate() {
    for(int i=0; i<numberOfFloorTiles; i++) {
        tileUpdate(&floorTiles[i]);
    }
}

void floorDraw() {
    for(int i=0; i<numberOfFloorTiles; i++) {
        drawTile(&floorTiles[i]);
    }
}
