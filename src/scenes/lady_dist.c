#include "lady_dist.h"
#include "../assets2banks.h"
#include "../engine/palettes.h"
#include "../engine/tilemap.h"
#include "../libs/SMSlib.h"

void lady_dist_init(void)
{
    SMS_waitForVBlank();
    load_palette(palette_black, PALETTE_BACKGROUND);
    clear_tilemap(0);

    SMS_mapROMBank(lady_dist_palette_bin_bank);
    SMS_loadBGPalette(lady_dist_palette_bin);
    SMS_loadPSGaidencompressedTiles(lady_dist_tiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(6, 0, lady_dist_tilemap_stmcompr);
}

void lady_dist_update(void)
{
    SMS_waitForVBlank();
}

void lady_dist_end(void)
{
    SMS_waitForVBlank();
    load_blank_tile(0);
    clear_tilemap(0);
}
