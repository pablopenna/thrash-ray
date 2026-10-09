#include "raylib.h"

#include "assets/assets.h"

#include "entity/player.h"
#include "entity/meteorite.h"

#include "system/spawn.h"


#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Ray Thrash"

void gameInit() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    assetsLoad();

    playerInit();
    meteoritesInit();

    // setupNewMeteorite((Vector2){100, 100}, (Vector2){0,0});
}

void gameUpdate() {
    float delta = GetFrameTime();
    playerUpdate(&player, delta);
    meteoritesUpdateAll(delta);

    processMeteoriteSpawn(delta, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void gameDraw() {
    BeginDrawing();
    ClearBackground(BLACK);

    playerDraw(&player);
    meteoritesDrawAll();

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
