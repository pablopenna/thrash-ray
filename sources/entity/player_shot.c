#include "player_shot.h"
#include "entity.h"
#include "raylib.h"

static PlayerShot shot = {};
static Vector2 points[10] = {};

PlayerShot* getPlayerShot() {
    return &shot;
}

void onPlayerShot(Entity* player, PlayerShot* shot) {
    Vector2 originPoint = (Vector2) {
        .x = player->position.x,
        .y = player->position.y - (player->sprites->frameHeight * player->animationState.scaleY)/2.0f};
    points[0] = (Vector2) {.x = originPoint.x, .y = originPoint.y};
    points[1] = (Vector2) {.x = originPoint.x - 25, .y = originPoint.y - 50};
    points[2] = (Vector2) {.x = originPoint.x + 25, .y = originPoint.y - 100};
    points[3] = (Vector2) {.x = originPoint.x, .y = originPoint.y - 150};

    shot->projectilePoints = points;
    shot->pointCount = 4;
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
