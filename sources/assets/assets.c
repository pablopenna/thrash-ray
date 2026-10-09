#include "assets.h"

Assets g_assets = {0};

void assetsLoad(void) {
    g_assets.thrashguy = LoadTexture(ASSETS_PATH "thrashguy.png");
    g_assets.meteorite = LoadTexture(ASSETS_PATH "meteorite.png");
}

void assetsUnload(void) {
    UnloadTexture(g_assets.thrashguy);
    UnloadTexture(g_assets.meteorite);
}
