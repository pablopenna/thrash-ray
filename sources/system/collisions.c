#include "raylib.h"

#include "collisions.h"
#include "entity/entity.h"
#include "entity/meteorite.h"
#include "system/floor.h"

void onFloorTileCollision(FloorTile* floorTile) {
    floorTile->isActive = false;
}

void onMeteoriteToFloorCollision(Entity* meteorite) {
    meteorite->data.meteor.active = false;
}

void onMeteoriteToMeteoriteCollision(Entity* meteorite) {
    meteorite->data.meteor.active = false;
}

void processMeteoriteFloorCollisions() {
    Entity* meteorites = getAllMeteorites();
    int numberOfFloorTiles = getNumberOfFloorTiles();

    for(int i=0;i<METEORITE_MAX_QUANTITY;i++) {
        Entity* currentMeteorite = &meteorites[i];
        if(!currentMeteorite->data.meteor.active) {
            continue;
        }

        for(int j=0; j<numberOfFloorTiles; j++) {
            FloorTile* currentFloorTile = getFloorTileAt(j);
            if(!currentFloorTile->isActive) {
                continue;
            }
            char collided = CheckCollisionRecs(getEntityEffectiveCollisionShape(currentMeteorite), currentFloorTile->rectangle);
            if(collided) {
                onFloorTileCollision(currentFloorTile);
                onMeteoriteToFloorCollision(currentMeteorite);
            }
        }
    }
}

void processMeteoriteMeteoriteCollisions() {
    Entity* meteorites = getAllMeteorites();

    for(int i=0;i<METEORITE_MAX_QUANTITY;i++) {
        Entity* aMeteor = &meteorites[i];
        if(!aMeteor->data.meteor.active) {
            continue;
        }

        for(int j=0; j<METEORITE_MAX_QUANTITY; j++) {
            if(i==j) {
                continue;
            }

            Entity* bMeteor = &meteorites[j];
            if(!bMeteor->data.meteor.active) {
                continue;
            }

            char collided = CheckCollisionRecs(getEntityEffectiveCollisionShape(aMeteor), getEntityEffectiveCollisionShape(bMeteor));
            if(collided) {
                onMeteoriteToMeteoriteCollision(aMeteor);
                onMeteoriteToMeteoriteCollision(bMeteor);
            }
        }
    }
}
