#include "eye.h"
#include "../assets2banks.h"
#include "../engine/palettes.h"
#include "../engine/tilemap.h"
#include "../libs/SMSlib.h"

void eye_init(void)
{
    SMS_waitForVBlank();
    load_palette(palette_black, PALETTE_BACKGROUND);
    clear_tilemap(0);

    SMS_mapROMBank(eye_big_palette_bin_bank);
    SMS_loadBGPalette(eye_big_palette_bin);
    SMS_loadPSGaidencompressedTiles(eye_big_tiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(4, 2, eye_big_tilemap_stmcompr);
}

void eye_update(void)
{
    SMS_waitForVBlank();
}

void eye_end(void)
{
    SMS_waitForVBlank();
    load_blank_tile(0);
    clear_tilemap(0);
}
