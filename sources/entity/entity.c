#include "config.h"
#include "entity.h"

#include "raymath.h"

Rectangle getEntityEffectiveCollisionShape(Entity *entity) {
    EntityAnimation *data = &entity->sprites[entity->animationState.currentAnimation];
    float xOffset = (data->frameWidth * entity->animationState.scaleX) / 2.0f;
    float yOffset = (data->frameHeight * entity->animationState.scaleY) / 2.0f;

    Rectangle collisionShape = (Rectangle){
        .x = entity->collisionShape.x + entity->position.x - xOffset,
        .y = entity->collisionShape.y + entity->position.y - yOffset,
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
        (Vector2){
            (data->frameWidth * state->scaleX) / 2.0f,
            (data->frameHeight * state->scaleY) / 2.0f
        }, // Center of the sprite so rotation pivot is its center
        state->rotationDeg,
        WHITE
    );

    #if DRAW_COLLISIONS
        Rectangle collisionShape = getEntityEffectiveCollisionShape(entity);
        DrawRectangleLinesEx(collisionShape, 1, RED);
    #endif
}
