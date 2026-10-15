#include "entity/player.h"
#include "collisions.h"
#include "entity/entity.h"
#include "entity/meteorite.h"
#include "entity/player_shot.h"
#include "system/floor.h"
#include "raylib.h"

// Helper function to check collisions between lines and rectangles
bool CheckCollisionLineStripRec(const Vector2 *points, int count, Rectangle rec)
{
    if (count < 1) return false;

    if (CheckCollisionPointRec(points[0], rec)) return true;

    Vector2 tl = { rec.x,             rec.y };
    Vector2 tr = { rec.x + rec.width, rec.y };
    Vector2 bl = { rec.x,             rec.y + rec.height };
    Vector2 br = { rec.x + rec.width, rec.y + rec.height };

    for (int i = 0; i < count - 1; i++) {
        Vector2 a = points[i];
        Vector2 b = points[i + 1];

        if(CheckCollisionLines(a, b, tl, tr, 0)) return true;
        if(CheckCollisionLines(a, b, tr, br, 0)) return true;
        if(CheckCollisionLines(a, b, br, bl, 0)) return true;
        if(CheckCollisionLines(a, b, bl, tl, 0)) return true;
    }

    return false;
}

void onPlayerFloorCollision(Entity* player, const Rectangle* collisionShape) {
   player->data.player.isGrounded = true;
   // prevent sinking into the floor
   player->position.y -= collisionShape->height - 1; // 1 pixel still collide with floor and not set isGrounded = false in next frame
}

void onPlayerNoFloorCollision(Entity* player) {
   player->data.player.isGrounded = false;
}

void onFloorTileCollision(FloorTile* floorTile) {
    floorTile->isActive = false;
}

void onMeteoriteToFloorCollision(Entity* meteorite) {
    meteorite->data.meteor.active = false;
}

void onMeteoriteToMeteoriteCollision(Entity* meteorite) {
    meteorite->data.meteor.active = false;
}

void onMeteoriteToPlayerShotCollision(Entity* meteorite) {
    meteorite->data.meteor.active = false;
}

void processPlayerFloorCollisions() {
    int numberOfFloorTiles = getNumberOfFloorTiles();
    Entity* player = getPlayer();

    for(int j=0; j<numberOfFloorTiles; j++) {
        FloorTile* currentFloorTile = getFloorTileAt(j);
        if(!currentFloorTile->isActive) {
            continue;
        }
        Rectangle collisionRect = GetCollisionRec(getEntityEffectiveCollisionShape(player), currentFloorTile->rectangle);
        if(collisionRect.height > 0 && collisionRect.width > 0) {
            onPlayerFloorCollision(player, &collisionRect);
            return;
        }
    }
    onPlayerNoFloorCollision(player);
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

void processPlayerShotMeteoriteCollisions() {
    Entity* meteorites = getAllMeteorites();
    PlayerShot *shot = getPlayerShot();

    if(!shot->isActive) return;

    for(int i=0;i<METEORITE_MAX_QUANTITY;i++) {
        Entity* currentMeteorite = &meteorites[i];
        if(!currentMeteorite->data.meteor.active) {
            continue;
        }

        bool hit = CheckCollisionLineStripRec(
            shot->projectilePoints,
            shot->pointCount,
            getEntityEffectiveCollisionShape(currentMeteorite)
        );

        if(hit) {
            onMeteoriteToPlayerShotCollision(currentMeteorite);
        }
    }
}
