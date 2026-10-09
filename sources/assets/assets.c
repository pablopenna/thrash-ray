#include "assets.h"

Assets g_assets = {0};

void AssetsLoad(void) {
    g_assets.thrashguy_idle = LoadTexture(ASSETS_PATH "thrashguy.png");
}

void AssetsUnload(void) {
    UnloadTexture(g_assets.thrashguy_idle);
}
