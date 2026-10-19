#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

typedef enum { ENTITY_PLAYER, ENTITY_METEOR } EntityType;

typedef struct PlayerShot PlayerShot; // Forward declaration
typedef struct {
    bool isGrounded;
    Vector2 velocity;
    bool isDead;
    PlayerShot *projectile;
} PlayerData;

typedef struct {
    bool active;
    Vector2 direction;
} MeteoriteData;

typedef struct {
    Texture2D spriteSheet;
    int frameWidth;
    int frameHeight;
    int frameStart; // From which frame the animation starts
    int frameCount; // How many frames the animation lasts (frames need to be together)
    float frameDuration;
} EntityAnimation;

typedef struct {
    int currentAnimation;
    float scaleX;
    float scaleY;
    float rotationDeg;
    int currentFrame;
    float frameDurationTimer;
} EntityAnimationState;

typedef struct State State; // Forward declaration to avoid circular dependency - cannot import state_machine.h
typedef struct {
    EntityType type;
    Vector2 position;
    float moveSpeed;
    Rectangle collisionShape;
    EntityAnimation *sprites; // Shared among instances of same type
    EntityAnimationState animationState; // unique per instance
    const State *currentState;
    union {
        PlayerData player;
        MeteoriteData meteor;
    } data;
} Entity;

Rectangle getEntityEffectiveCollisionShape(Entity *e);
/** Updates frame index of the animation if enough time has passed. */
void updateEntityAnimation(Entity *e, float delta);
/** Moves entity in the given direction */
void entityMoveByDirection(Entity *e, Vector2 direction, float delta);
/** Draws current sprite of the entity */
void drawEntity(Entity *e);

#endif
