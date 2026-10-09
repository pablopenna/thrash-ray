#ifndef ASSETS_H
#define ASSETS_H

#include "raylib.h"

typedef struct {
    Texture2D thrashguy;
    Texture2D meteorite;
} Assets;

extern Assets g_assets;

void assetsLoad(void);
void assetsUnload(void);

#endif
