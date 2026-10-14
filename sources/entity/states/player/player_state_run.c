#include "config.h"
#include "entity/player.h"
#include "entity/states/state_machine.h"
#include "entity/states/player/player_state_air.h"
#include "entity/states/player/player_state_jump.h"
#include "entity/states/player/player_state_idle.h"
#include "entity/states/player/player_state_run.h"

static void enter(Entity *e, const State *previousState) {
    e->animationState.currentAnimation = PLAYER_ANIM_IDLE;
}

static void update(Entity *player, float delta) {
    if (IsKeyPressed(KEY_SPACE)) {
        changeState(player, &PLAYER_STATE_JUMP);
        return;
    }

    if(!player->data.player.isGrounded) {
        changeState(player, &PLAYER_STATE_AIR);
        return;
    }

    int xDirection = 0;
    if(IsKeyDown(PLAYER_INPUT_MOVE_LEFT)) {
        xDirection -= 1;
    }
    if(IsKeyDown(PLAYER_INPUT_MOVE_RIGHT)) {
        xDirection = 1;
    }
    if(xDirection == 0) {
        changeState(player, &PLAYER_STATE_IDLE);
        return;
    }
    player->data.player.velocity.x = xDirection * player->moveSpeed;
    player->position.x += player->data.player.velocity.x * delta;
}

static void exit(Entity *e) {}

// A statically defined State value.
const State PLAYER_STATE_RUN = {
    .enter  = enter,
    .update = update,
    .exit   = exit,
    .name = "RUN",
};
