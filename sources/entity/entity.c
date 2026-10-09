#include "entity.h"

Rectangle getEntityEffectiveCollisionShape(Entity *player) {
    Rectangle collisionShape = (Rectangle){
        .x = player->collisionShape.x + player->position.x,
        .y = player->collisionShape.y + player->position.y,
        .width = player->collisionShape.width * player->scaleX,
        .height = player->collisionShape.height * player->scaleY,
    };
    return collisionShape;
}
