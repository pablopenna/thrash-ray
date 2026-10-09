#ifndef ASSETS_H
#define ASSETS_H

#include "raylib.h"

typedef struct {
    Texture2D thrashguy_idle;
} Assets;

extern Assets g_assets;

void AssetsLoad(void);
void AssetsUnload(void);

#endif
