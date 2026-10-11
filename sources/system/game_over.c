#include "entity/player.h"
#include "raylib.h"
#include "system/floor.h"
#include "game_over.h"

static bool isGameOver = false;

void processGameOver() {
    Entity* player = getPlayer();
    if(isEntityUnderFloor(player)) {
        player->data.player.isDead = true;
        isGameOver = true;
    }
}

void drawGameOver() {
    if(!isGameOver) return;

    const char* text = "GAME OVER!";
    const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 40, 1);
    DrawText(text, (float)GetScreenWidth() / 2 - text_size.x / 2, text_size.y + 50, 40, RAYWHITE);
}
