#include "intro.h"
#include "../assets2banks.h"
#include "../engine/global_variables.h"
#include "../engine/scenes.h"
#include "../engine/tilemap.h"
#include "../libs/SMSlib.h"

void intro_scene_init(void)
{
    SMS_mapROMBank(da_mini_palette_bin_bank);
    SMS_loadPSGaidencompressedTiles(da_mini_tiles_psgcompr, 1);
    SMS_loadBGPalette(da_mini_palette_bin);
}

void intro_scene_update(void)
{
    if (frame_count == 24)
    {
        SMS_loadSTMcompressedTileMap(11, 12, da_mini_tilemap_stmcompr);
    }
    else if (frame_count == 192)
    {
        clear_tilemap(0);
    }

    waitForFrame();
}

void intro_scene_end(void) {}
