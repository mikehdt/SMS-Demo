#include "grid.h"
#include "../assets2banks.h" // Generated with the assets task
#include "../libs/SMSlib.h"

void init_background(void)
{
    SMS_loadPSGaidencompressedTiles(grid_tiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(0, 0, grid_tilemap_stmcompr);
    SMS_loadBGPalette(grid_palette_bin);
}

void animate_background(void)
{
}

void init_sprites(void)
{
}

void animate_sprites(void)
{
}
