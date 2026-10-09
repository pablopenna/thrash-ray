#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

typedef enum { ENTITY_PLAYER, ENTITY_METEOR } EntityType;

typedef struct {
    Texture2D spriteSheet;
    int frameWidth;
    int frameHeight;
    int frameCount;
    float frameDuration;
    float frameDurationTimer;
    int currentFrame;
} EntitySprite;

typedef struct {
    EntityType type;
    Vector2 position;
    float moveSpeed;
    int spriteCount;
    int currentSprite;
    float scaleX;
    float scaleY;
    Rectangle collisionShape;
    EntitySprite *sprites; // An entity should have 1 to n sprites. Points at a static array, not owned
    union {
        struct { int score; int hp; } player;
        struct { int size; } meteor;
    } data;
} Entity;

typedef struct {
    int count;
    Entity *entities;
} EntityRegistry;

Rectangle getEntityEffectiveCollisionShape(Entity *e);

#endif
