#include "config.h"
#include "entity/player.h"
#include "entity/states/state_machine.h"
#include "entity/states/player/player_state_air.h"
#include "entity/states/player/player_state_jump.h"
#include "entity/states/player/player_state_idle.h"
#include "entity/states/player/player_state_run.h"
#include "entity/states/player/player_state_rotate.h"

#include "raylib.h"

static void enter(Entity *e, const State *previousState) {
    e->animationState.currentAnimation = PLAYER_ANIM_IDLE;
}

static void update(Entity *e, float delta) {
    if(!e->data.player.isGrounded) {
        changeState(e, &PLAYER_STATE_AIR);
        return;
    }

    if (IsKeyDown(PLAYER_INPUT_MOVE_LEFT) || IsKeyDown(PLAYER_INPUT_MOVE_RIGHT)) {
        changeState(e, &PLAYER_STATE_RUN);
        return;
    }

    if (IsKeyPressed(PLAYER_INPUT_JUMP)) {
        changeState(e, &PLAYER_STATE_JUMP);
        return;
    }

    if (IsKeyPressed(PLAYER_INPUT_ROTATE_LEFT) || IsKeyPressed(PLAYER_INPUT_ROTATE_RIGHT)) {
        changeState(e, &PLAYER_STATE_ROTATE);
        return;
    }
}

static void exit(Entity *e) {}

// A statically defined State value.
const State PLAYER_STATE_IDLE = {
    .enter  = enter,
    .update = update,
    .exit   = exit,
    .name = "IDLE",
};
