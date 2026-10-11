#include "player.h"
#include "assets/assets.h"
#include "entity.h"
#include "raylib.h"

static EntityAnimation playerSprites[PLAYER_MAX_ANIM] = {
    [PLAYER_ANIM_IDLE] = {
        .frameWidth = 32,
        .frameHeight = 32,
        .frameStart = 0,
        .frameCount = 3,
        .frameDuration = 0.15f,
    }
};

static Entity player = {
    .position = { 400, 300 },
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

Entity* getPlayer() {
    return &player;
}

void playerInit() {
    playerSprites[PLAYER_ANIM_IDLE].spriteSheet = g_assets.thrashguy;
}

void playerUpdate(float delta) {
    Entity* player = getPlayer();
    updateEntityAnimation(player, delta);
    player->animationState.rotation += delta * 100.0f;

    // Horizontal movement
    int xDirection = 0;
    if(IsKeyDown(KEY_A)) {
        xDirection -= 1;
    }
    if(IsKeyDown(KEY_D)) {
        xDirection = 1;
    }
    player->data.player.velocity.x = xDirection * player->moveSpeed;
    player->position.x += player->data.player.velocity.x * delta;

    // Horizontal movement - Air
    if(player->data.player.isGrounded) {
        player->data.player.velocity.y = 0;
    }

    float jumpSpeed = 500.0f;
    if (player->data.player.isGrounded && IsKeyPressed(KEY_SPACE)) {
        player->data.player.velocity.y -= jumpSpeed;
    }

    float gravity = 15.0f;
    if(!player->data.player.isGrounded) {
        player->data.player.velocity.y += gravity;

        if(IsKeyReleased(KEY_SPACE) && player->data.player.velocity.y < 0) {
            player->data.player.velocity.y *= 0.5f;   // kill half the upward speed
        }
    }

    player->position.y += player->data.player.velocity.y * delta;
}

void playerDraw() {
    Entity* player = getPlayer();
    drawEntity(player);
}
