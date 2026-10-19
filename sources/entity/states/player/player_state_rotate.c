#include "config.h"
#include "entity/player.h"
#include "entity/states/state_machine.h"
#include "entity/states/player/player_state_air.h"
#include "raylib.h"
#include "raymath.h"

static void enter(Entity *e, const State *previousState) {
    e->animationState.currentAnimation = PLAYER_ANIM_IDLE;
}

static void update(Entity *player, float delta) {
    float *rotation = &player->animationState.rotationDeg;
    if(!IsKeyDown(PLAYER_INPUT_ROTATE_LEFT) && !IsKeyDown(PLAYER_INPUT_ROTATE_RIGHT) && FloatEquals(*rotation, 0)) {
        changeState(player, &PLAYER_STATE_AIR);
        return;
    }

    if(!player->data.player.isGrounded) {
        player->data.player.velocity.y += GRAVITY;
        player->position.y += player->data.player.velocity.y * delta;
    }

    if(IsKeyDown(PLAYER_INPUT_ROTATE_LEFT)) {
        *rotation -= PLAYER_ROTATION_SPEED * delta;
        return;
    }

    if(IsKeyDown(PLAYER_INPUT_ROTATE_RIGHT)) {
        *rotation += PLAYER_ROTATION_SPEED * delta;
        return;
    }

    *rotation = Lerp(*rotation, 0.0, PLAYER_ROTATION_SPEED/5 * delta);
    if(fabsf(*rotation) < 10.0f) {
        *rotation = 0.0f;
    }
}

static void exit(Entity *e) {

}

// A statically defined State value.
const State PLAYER_STATE_ROTATE = {
    .enter  = enter,
    .update = update,
    .exit   = exit,
    .name = "ROTATE",
};
