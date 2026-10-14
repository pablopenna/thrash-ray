#include "raylib.h"

#include "config.h"

#include "assets/assets.h"

#include "entity/player.h"
#include "entity/meteorite.h"

#include "system/collisions.h"
#include "system/game_over.h"
#include "system/spawn.h"
#include "system/floor.h"

void gameInit() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(TARGET_FPS);

    assetsLoad();

    playerInit();
    meteoritesInit();
    floorInit();
}

void gameUpdate() {
    processPlayerFloorCollisions();
    processMeteoriteFloorCollisions();
    processMeteoriteMeteoriteCollisions();

    float delta = GetFrameTime();
    playerUpdate(delta);
    meteoritesUpdateAll(delta);
    floorUpdate();

    processMeteoriteSpawn(delta);

    processGameOver();
}

void gameDraw() {
    BeginDrawing();
    ClearBackground(BLACK);

    playerDraw();
    meteoritesDrawAll();
    floorDraw();

    drawGameOver();

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
