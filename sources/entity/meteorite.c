#include "meteorite.h"
#include "assets/assets.h"
#include "entity.h"
#include "raylib.h"
#include "raymath.h"

#include "stdio.h"

// shared by every meteorite, never freed.
static EntityAnimation meteorite_sprites[] = {
    [METEORITE_ANIM_IDLE] = {
        .frameWidth = 32,
        .frameHeight = 32,
        .frameCount = 1,
    },
    [METEORITE_ANIM_MOVE] = {
        .frameWidth = 32,
        .frameHeight = 32,
        .frameStart = 1,
        .frameCount = 4,
        .frameDuration = 0.15f,
    }
};

static Entity meteorite_pool[METEORITE_MAX_QUANTITY] = {0};

Entity* getAllMeteorites() {
    return meteorite_pool;
}

// Returns by value
Entity meteoriteCreate() {
  return (Entity){
      .type = ENTITY_METEOR,
      .position = {0,0},
      .collisionShape = {8,22, 24, 22},
      .moveSpeed = 150.0f,
      .sprites = meteorite_sprites,
      .animationState = {
          .currentAnimation = METEORITE_ANIM_IDLE,
          .scaleX = 2.0,
          .scaleY = 2.0,
      },
      .data.meteor = {
       .active = false
      },
  };
}

/**
 * Initializes the pool and the textures
 */
void meteoritesInit() {
    meteorite_sprites[METEORITE_ANIM_IDLE].spriteSheet = g_assets.meteorite;
    meteorite_sprites[METEORITE_ANIM_MOVE].spriteSheet = g_assets.meteorite;

    for (int i = 0; i < METEORITE_MAX_QUANTITY; i++) {
        meteorite_pool[i] = meteoriteCreate();
    }
}

/** Setup a meteorite from the pool and make it active */
Entity* setupNewMeteorite(Vector2 position, Vector2 direction) {
    int unusedIndex = -1;
    for(int i=0; i<METEORITE_MAX_QUANTITY; i++) {
        Entity* meteorite = &meteorite_pool[i];
        if(!meteorite->data.meteor.active) {
            unusedIndex = i;
            break;
        }
    }

    if(unusedIndex == -1) {
        printf("[ERROR] Out of space for more meteorites");
        return 0;
    }

    Entity* meteorite = &meteorite_pool[unusedIndex];
    meteorite->data.meteor.active = true;
    meteorite->data.meteor.direction = direction;
    meteorite->position = position;
    meteorite->animationState.rotation = Vector2Angle(
        (Vector2) {0, 1}, // Meteorite sprite is facing down
        direction
    ) * RAD2DEG;
    meteorite->animationState.currentAnimation = METEORITE_ANIM_MOVE;

    return meteorite;
}

void meteoriteUpdate(Entity* meteorite, float delta) {
    updateEntityAnimation(meteorite, delta);
    entityMoveByDirection(meteorite, meteorite->data.meteor.direction, delta);

    int screen_height = 450; // TODO: get window_size or playable area;
    if(meteorite->position.y > screen_height) {
        meteorite->data.meteor.active = false;
    }
}

void meteoritesUpdateAll(float delta) {
    for(int i=0; i<METEORITE_MAX_QUANTITY; i++) {
        Entity* meteorite = &meteorite_pool[i];
        if(!meteorite->data.meteor.active) {
            continue;
        }
        meteoriteUpdate(meteorite, delta);
    }
}

void meteoriteDraw(Entity* meteorite) {
    drawEntity(meteorite);
}

void meteoritesDrawAll() {
    for(int i=0; i<METEORITE_MAX_QUANTITY; i++) {
        Entity* meteorite = &meteorite_pool[i];
        if(!meteorite->data.meteor.active) {
            continue;
        }
        meteoriteDraw(meteorite);
    }
}
