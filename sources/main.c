#include "raylib.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Ray Thrash"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    Texture2D texture = LoadTexture(ASSETS_PATH"test.png"); // Check README.md for how this WORKS

    // Setup player sprite
    Texture2D playersheet = LoadTexture(ASSETS_PATH"thrashguy.png");
    const int FRAME_COUNT = 3;
    const float SCALE = 2.0f;
    int frameWidth = playersheet.width/FRAME_COUNT;
    int frameHeight = playersheet.height;
    int currentFrame = 0;
    float timer = 0.0f;
    float frameTime = 0.15f;

    Vector2 playerPos = (Vector2){0.0f, 0.0f};
    float playerMoveSpeed = 250.0f;

    while (!WindowShouldClose()) {
        float delta = GetFrameTime();

        //Player animation
        timer += delta;
        if(timer >= frameTime) {
            timer = 0.0f;
            currentFrame = (currentFrame + 1) % FRAME_COUNT;
        }
        Rectangle playerSpriteSource = {
            (float) (currentFrame * frameWidth),
            0.0f,
            (float) frameWidth,
            (float) frameHeight
        };

        if(IsKeyDown(KEY_A)) {
            playerPos.x -= playerMoveSpeed * delta;
        }
        if(IsKeyDown(KEY_D)) {
            playerPos.x += playerMoveSpeed * delta;
        }
        if(IsKeyDown(KEY_W)) {
            playerPos.y -= playerMoveSpeed * delta;
        }
        if(IsKeyDown(KEY_S)) {
            playerPos.y += playerMoveSpeed * delta;
        }

        Rectangle playerSpriteDest = {
            playerPos.x, playerPos.y, (float) frameWidth * SCALE,(float) frameHeight * SCALE
        };

        BeginDrawing();

        ClearBackground(BLACK);

        // Hello World image
        const int texture_x = SCREEN_WIDTH / 2 - texture.width / 2;
        const int texture_y = SCREEN_HEIGHT / 2 - texture.height / 2;
        DrawTexture(texture, texture_x, texture_y, RED);

        const char* text = "OMG! IT WORKS!";
        const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
        DrawText(text, SCREEN_WIDTH / 2 - text_size.x / 2, texture_y + texture.height + text_size.y + 10, 20, RAYWHITE);

        // Player sprite
        DrawTexturePro(playersheet, playerSpriteSource, playerSpriteDest, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
