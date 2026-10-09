#include "entity.h"

#include "raymath.h"

Rectangle getEntityEffectiveCollisionShape(Entity *entity) {
    Rectangle collisionShape = (Rectangle){
        .x = entity->collisionShape.x + entity->position.x,
        .y = entity->collisionShape.y + entity->position.y,
        .width = entity->collisionShape.width * entity->animationState.scaleX,
        .height = entity->collisionShape.height * entity->animationState.scaleY,
    };
    return collisionShape;
}

void updateEntityAnimation(Entity *entity, float delta) {
    EntityAnimationState *state = &entity->animationState;
    EntityAnimation *data = &entity->sprites[state->currentAnimation];

    state->frameDurationTimer += delta;
    if(state->frameDurationTimer >= data->frameDuration) {
        state->frameDurationTimer = 0.0f;
        state->currentFrame = ((state->currentFrame + 1) % data->frameCount) + data->frameStart;
    }
}

void entityMoveByDirection(Entity *e, Vector2 direction, float delta) {
    e->position = Vector2Add(
        e->position,
        Vector2Scale(direction, e->moveSpeed * delta));
}

void drawEntity(Entity *entity) {
    EntityAnimationState *state = &entity->animationState;
    EntityAnimation *data = &entity->sprites[state->currentAnimation];

    Rectangle spriteSource = {
        (float) (state->currentFrame * data->frameWidth),
        0.0f,
        (float) data->frameWidth,
        (float) data->frameHeight,
    };

    Rectangle spriteDest = {
        entity->position.x,
        entity->position.y,
        (float) data->frameWidth * state->scaleX,
        (float) data->frameHeight * state->scaleY,
    };

    DrawTexturePro(
        data->spriteSheet,
        spriteSource,
        spriteDest,
        (Vector2){0.0f, 0.0f},
        0.0f,
        WHITE
    );

    if(DRAW_COLLISIONS) {
        Rectangle collisionShape = getEntityEffectiveCollisionShape(entity);
        DrawRectangleLinesEx(collisionShape, 1, RED);
    }
}
