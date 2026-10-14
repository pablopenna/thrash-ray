#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "entity/entity.h"

typedef void (*StateEnterFn)(Entity *self, const State* previousState);
typedef void (*StateUpdateFn)(Entity *self, float delta);
typedef void (*StateExitFn)(Entity *self);

// Completes forward declaration in entity.h
struct State {
    StateEnterFn enter;
    StateUpdateFn update;
    StateExitFn exit;
    const char* name; // For debug purposes only
};

void changeState(Entity *actor, const State* state);
void runCurrentState(Entity *actor, const float delta);

#endif
