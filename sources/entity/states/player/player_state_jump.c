#include "config.h"
#include "entity/player.h"
#include "entity/states/state_machine.h"
#include "entity/states/player/player_state_jump.h"
#include "entity/states/player/player_state_air.h"

static void enter(Entity *e, const State *previousState) {
    e->animationState.currentAnimation = PLAYER_ANIM_IDLE;
}

static void update(Entity *player, float delta) {
    player->data.player.velocity.y += GRAVITY - PLAYER_JUMP_SPEED;
    player->position.y += player->data.player.velocity.y * delta;

    changeState(player, &PLAYER_STATE_AIR);
}

static void exit(Entity *e) {}

// A statically defined State value.
const State PLAYER_STATE_JUMP = {
    .enter  = enter,
    .update = update,
    .exit   = exit,
    .name = "JUMP",
};
