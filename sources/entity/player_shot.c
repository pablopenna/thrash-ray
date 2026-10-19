#include "player_shot.h"
#include "entity.h"
#include "raylib.h"
#include "raymath.h"

#define SHOT_POINTS 4

static PlayerShot shot = {};
static Vector2 base_shot_points[SHOT_POINTS] = {
    (Vector2) {.x = 0, .y = 0},
    (Vector2) {.x = -25, .y = -50},
    (Vector2) {.x = 25, .y = -100},
    (Vector2) {.x = 0, .y = -150},
};
static Vector2 shot_points[SHOT_POINTS] = {};

PlayerShot* getPlayerShot() {
    return &shot;
}

void applyTransformations(Entity* player) {
    Vector2 playerShootingPoint = (Vector2) {
        .x = player->position.x,
        .y = player->position.y - (player->sprites->frameHeight * player->animationState.scaleY)/2.0f
    };

    // transform
    for(int i=0;i<SHOT_POINTS;i++) {
        shot_points[i] = Vector2Add(playerShootingPoint, base_shot_points[i]);
    }

    // rotation
    Vector2 pivot = playerShootingPoint;
    for (int i=0;i<SHOT_POINTS;i++) {
        Vector2 rel = Vector2Subtract(shot_points[i], pivot); // pivot -> origin
        rel = Vector2Rotate(rel, player->animationState.rotationDeg * DEG2RAD); // rotate
        shot_points[i] = Vector2Add(rel, pivot); // origin -> pivot back
    }
}

void onPlayerShot(Entity* player, PlayerShot* shot) {
    applyTransformations(player);

    shot->projectilePoints = shot_points;
    shot->pointCount = SHOT_POINTS;
    shot->duration = 0.5f;
    shot->timer = 0.0f;
    shot->isActive = true;
}

void playerShotUpdate(float delta) {
    PlayerShot *shot = getPlayerShot();
    if(!shot->isActive) return;

    shot->timer += delta;
    if(shot->timer > shot->duration) {
        shot->isActive = false;
    }
}

void playerShotDraw() {
    PlayerShot *shot = getPlayerShot();
    if(!shot->isActive) return;

    DrawLineStrip(shot->projectilePoints, shot->pointCount, RAYWHITE);
}
