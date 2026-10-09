#include "player.h"
#include "entity/entity.h"
#include "raylib.h"

#define PLAYER_ANIM_IDLE 0
#define PLAYER_MAX_ANIM 1

#define DRAW_COLLISION 1

static EntitySprite playerSprites[PLAYER_MAX_ANIM] = {
    [PLAYER_ANIM_IDLE] = {
        .frameWidth = 32,
        .frameHeight = 32,
        .frameCount = 3,
        .frameDuration = 0.15f,
        .frameDurationTimer = 0.0f,
        .currentFrame = 0,
    }
};

Entity player = {
    .position = { 0, 0 },
    .moveSpeed = 250.0f,
    .spriteCount = PLAYER_MAX_ANIM,
    .currentSprite = PLAYER_ANIM_IDLE,
    .scaleX = 2.0f,
    .scaleY = 2.0f,
    .collisionShape = {
        .x = 0,
        .y = 0,
        .width = 32,
        .height = 32,
    },
    .sprites = playerSprites,
};

void playerInit(EntityRegistry *registry) {
    playerSprites[PLAYER_ANIM_IDLE].spriteSheet = LoadTexture(ASSETS_PATH"thrashguy.png");
}

void playerUpdate(Entity *player, float delta) {
    EntitySprite *currentSprite = &player->sprites[player->currentSprite];
    currentSprite->frameDurationTimer += delta;
    if(currentSprite->frameDurationTimer >= currentSprite->frameDuration) {
        currentSprite->frameDurationTimer = 0.0f;
        currentSprite->currentFrame = (currentSprite->currentFrame + 1) % currentSprite->frameCount;
    }

    if(IsKeyDown(KEY_A)) {
        player->position.x -= player->moveSpeed * delta;
    }
    if(IsKeyDown(KEY_D)) {
        player->position.x += player->moveSpeed * delta;
    }
    if(IsKeyDown(KEY_W)) {
        player->position.y -= player->moveSpeed * delta;
    }
    if(IsKeyDown(KEY_S)) {
        player->position.y += player->moveSpeed * delta;
    }
}

void playerDraw(Entity *player) {
    EntitySprite *currentSprite = &player->sprites[player->currentSprite];
    Rectangle playerSpriteSource = {
        (float) (currentSprite->currentFrame * currentSprite->frameWidth),
        0.0f,
        (float) currentSprite->frameWidth,
        (float) currentSprite->frameHeight,
    };

    Rectangle playerSpriteDest = {
        player->position.x,
        player->position.y,
        (float) currentSprite->frameWidth * player->scaleX,
        (float) currentSprite->frameHeight * player->scaleY,
    };

    DrawTexturePro(
        currentSprite->spriteSheet,
        playerSpriteSource,
        playerSpriteDest,
        (Vector2){0.0f, 0.0f},
        0.0f,
        WHITE
    );

    if(DRAW_COLLISION) {
        Rectangle playerCollisionShape = getEntityEffectiveCollisionShape(player);
        DrawRectangleLinesEx(playerCollisionShape, 1, RED);
    }
}
