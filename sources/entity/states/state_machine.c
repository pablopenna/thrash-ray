#include "state_machine.h"

void changeState(Entity *actor, const State* newState) {
    const State* previousState = actor->currentState;
    actor->currentState->exit(actor);
    actor->currentState = newState;
    actor->currentState->enter(actor, previousState);
}

void runCurrentState(Entity *actor, const float delta){
    actor->currentState->update(actor, delta);
}
