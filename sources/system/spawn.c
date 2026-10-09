#include "raylib.h"
#include "raymath.h"

#include "entity/meteorite.h"

static float spawnCooldown = 1.0f;
static float timer = 1000.0f;


void spawnMeteorite(int screenWidth, int screenHeight) {
    Vector2 origin = { GetRandomValue(0, screenWidth), 0};
    Vector2 destination = { GetRandomValue(0, screenWidth), screenHeight};
    Vector2 direction = Vector2Normalize(Vector2Subtract(destination, origin));

    setupNewMeteorite(origin, direction);
}

void processMeteoriteSpawn(float delta, int screenWidth, int screenHeight) {
    timer += delta;
    if(timer >= spawnCooldown) {
        timer = 0;
        spawnMeteorite(screenWidth, screenHeight);
    }
}
