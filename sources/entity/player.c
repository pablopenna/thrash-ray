#include "player.h"
#include "assets/assets.h"
#include "entity.h"
#include "raylib.h"
#include "raymath.h"

static EntityAnimation playerSprites[PLAYER_MAX_ANIM] = {
    [PLAYER_ANIM_IDLE] = {
        .frameWidth = 32,
        .frameHeight = 32,
        .frameStart = 0,
        .frameCount = 3,
        .frameDuration = 0.15f,
    }
};

Entity player = {
    .position = { 0, 0 },
    .moveSpeed = 250.0f,
    .animationState = {
        .currentAnimation = PLAYER_ANIM_IDLE,
        .scaleX = 2.0,
        .scaleY = 2.0,
    },
    .collisionShape = {
        .x = 0,
        .y = 0,
        .width = 32,
        .height = 32,
    },
    .sprites = playerSprites,
};

void playerInit() {
    playerSprites[PLAYER_ANIM_IDLE].spriteSheet = g_assets.thrashguy;
}

void playerUpdate(Entity *player, float delta) {
    updateEntityAnimation(player, delta);

    Vector2 direction = {0,0};
    if(IsKeyDown(KEY_A)) {
        direction.x -= 1;
    }
    if(IsKeyDown(KEY_D)) {
        direction.x = 1;
    }
    if(IsKeyDown(KEY_W)) {
        direction.y -= 1;
    }
    if(IsKeyDown(KEY_S)) {
        direction.y += 1;
    }
    direction = Vector2Normalize(direction);

    player->position.x += direction.x * player->moveSpeed * delta;
    player->position.y += direction.y * player->moveSpeed * delta;
}

void playerDraw(Entity *player) {
    drawEntity(player);
}
