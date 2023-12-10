#include "../assets2banks.h"
#include "../engine/scenes.h"
#include "../engine/tilemap.h"
#include "../libs/SMSlib.h"

void logo_init(void)
{
    SMS_displayOff();

    wait_for_frame();

    SMS_mapROMBank(da_mini_palette_bin_bank);
    SMS_loadBGPalette(da_mini_palette_bin);
    SMS_loadPSGaidencompressedTiles(da_mini_tiles_psgcompr, 1);
    SMS_loadSTMcompressedTileMap(11, 12, da_mini_tilemap_stmcompr);
    SMS_displayOn();
}

void logo_update(void)
{
    wait_for_frame();
}

void logo_end(void)
{
    wait_for_frame();
    clear_tilemap(0);
}
