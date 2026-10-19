#include "player.h"
#include "player_shot.h"
#include "assets/assets.h"
#include "config.h"
#include "entity.h"
#include "entity/states/player/player_state_idle.h"
#include "entity/states/state_machine.h"
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
    .currentState = &PLAYER_STATE_IDLE,
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
    runCurrentState(player, delta);

    if(IsKeyPressed(PLAYER_INPUT_SHOOT)) {
        PlayerShot* shot = getPlayerShot();
        onPlayerShot(player, shot);
    }
}

void playerDraw() {
    Entity* player = getPlayer();
    if(player->data.player.isDead) return;

    drawEntity(player);
}
