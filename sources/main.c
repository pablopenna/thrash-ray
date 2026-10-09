#include "raylib.h"
#include "entity/player.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Ray Thrash"

static EntityRegistry registry = {};

void gameInit() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    playerInit(&registry);
}

void gameUpdate() {
    float delta = GetFrameTime();
    playerUpdate(&player, delta);
}

void gameDraw() {
    BeginDrawing();
    ClearBackground(BLACK);

    playerDraw(&player);

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
