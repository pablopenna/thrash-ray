#include "raylib.h"

#include "assets/assets.h"

#include "entity/player.h"
#include "entity/meteorite.h"

#include "system/collisions.h"
#include "system/spawn.h"
#include "system/floor.h"


#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Ray Thrash"

void gameInit() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    assetsLoad();

    playerInit();
    meteoritesInit();
    floorInit();
}

void gameUpdate() {
    processMeteoriteFloorCollisions();
    processMeteoriteMeteoriteCollisions();

    float delta = GetFrameTime();
    playerUpdate(&player, delta);
    meteoritesUpdateAll(delta);
    floorUpdate();

    processMeteoriteSpawn(delta);
}

void gameDraw() {
    BeginDrawing();
    ClearBackground(BLACK);

    playerDraw(&player);
    meteoritesDrawAll();
    floorDraw();

    EndDrawing();
}

int main(void)
{
    gameInit();

    while (!WindowShouldClose()) {
        gameUpdate();
        gameDraw();
    }

    CloseWindow();

    return 0;
}
