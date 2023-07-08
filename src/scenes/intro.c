#include "intro.h"
#include "../assets2banks.h"
#include "../engine/audio.h"
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
    wait_for_frame();
}

void intro_scene_end(void) {}
