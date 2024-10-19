#include "lady.h"
#include "../assets2banks.h"
#include "../engine/palettes.h"
#include "../engine/scenes.h"
#include "../engine/tilemap.h"
#include "../libs/SMSlib.h"

void lady_init(void)
{
    cur_stage = 1;

    SMS_waitForVBlank();
    load_palette(palette_black, PALETTE_BACKGROUND);

    clear_tilemap(0);
    SMS_mapROMBank(lady_palette_bin_bank);
    SMS_loadBGPalette(palette_black);
    SMS_loadPSGaidencompressedTiles(lady_tiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(6, 0, lady_tilemap_stmcompr);
}

void lady_update(void)
{
    uint8_t i;

    if (cur_stage == 1)
    {
        for (i = 0; i < 10; i++)
        {
            fade_from_black(lady_palette_bin, i);

            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
        }

        cur_stage = 2;
    }

    SMS_waitForVBlank();

    if (cur_frame++ > 90)
    {
        for (i = 0; i < 10; i++)
        {
            fade_to_white(lady_palette_bin, i);

            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
        }

        next_scene();
    }
}

void lady_end(void)
{
    SMS_waitForVBlank();
    load_blank_tile(0);
    clear_tilemap(0);
}
