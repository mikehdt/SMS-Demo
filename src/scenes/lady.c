#include "../assets2banks.h"
#include "../engine/palettes.h"
#include "../engine/scenes.h"
#include "../engine/tilemap.h"
#include "../libs/SMSlib.h"
#include "lady.h"

void lady_init(void)
{
    SMS_displayOff();
    SMS_waitForVBlank();
    load_palette(palette_black, PALETTE_BACKGROUND);

    // TODO: clear the tilemap first
    SMS_mapROMBank(lady_palette_bin_bank);
    SMS_loadBGPalette(lady_palette_bin);
    SMS_loadPSGaidencompressedTiles(lady_tiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(6, 0, lady_tilemap_stmcompr);
    SMS_displayOn();
}

void lady_update(void)
{
    SMS_waitForVBlank();

    if (cur_frame++ > 50)
        next_scene();
}

void lady_end(void)
{
    SMS_waitForVBlank();
    load_blank_tile(0);
    clear_tilemap(0);
}
