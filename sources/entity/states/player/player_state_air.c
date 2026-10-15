#include "config.h"
#include "entity/player.h"
#include "entity/states/player/player_state_idle.h"
#include "entity/states/player/player_state_run.h"
#include "entity/states/state_machine.h"
#include "entity/states/player/player_state_air.h"

#include "raymath.h"

static bool has_speed_been_reduced;

static void enter(Entity *e, const State *previousState) {
    has_speed_been_reduced = false;
    e->animationState.currentAnimation = PLAYER_ANIM_IDLE;
}

static void update(Entity *player, float delta) {
    if(player->data.player.isGrounded) {
        player->data.player.velocity.y = 0;

        if(!FloatEquals(player->data.player.velocity.x, 0.0f)) {
            changeState(player, &PLAYER_STATE_RUN);
        } else {
            changeState(player, &PLAYER_STATE_IDLE);
        }
        return;
    }

    int xDirection = 0;
    if(IsKeyDown(PLAYER_INPUT_MOVE_LEFT)) {
        xDirection -= 1;
    }
    if(IsKeyDown(PLAYER_INPUT_MOVE_RIGHT)) {
        xDirection = 1;
    }
    player->data.player.velocity.x = xDirection * player->moveSpeed;
    player->position.x += player->data.player.velocity.x * delta;

    player->animationState.rotation += xDirection * PLAYER_ROTATION_SPEED *delta;

    player->data.player.velocity.y += GRAVITY;
    if(!has_speed_been_reduced && IsKeyReleased(KEY_SPACE) && player->data.player.velocity.y < 0) {
        player->data.player.velocity.y *= 0.5f;   // kill half the upward speed
        has_speed_been_reduced = true;
    }

    player->position.y += player->data.player.velocity.y * delta;
}

static void exit(Entity *player) {
    player->animationState.rotation = 0;
}

// A statically defined State value.
const State PLAYER_STATE_AIR = {
    .enter  = enter,
    .update = update,
    .exit   = exit,
    .name = "AIR",
};
