#include "../assets2banks.h"
#include "../engine/palettes.h"
#include "../engine/scenes.h"
#include "../engine/tilemap.h"
#include "../libs/SMSlib.h"
#include "lady.h"

void skull_init(void)
{
    cur_stage = 1;

    SMS_waitForVBlank();
    load_palette(palette_black, PALETTE_BACKGROUND);

    clear_tilemap(0);
    SMS_mapROMBank(lady_palette_bin_bank);
    SMS_loadBGPalette(palette_black);
    SMS_loadPSGaidencompressedTiles(lady_tiles_psgcompr, 0);
    SMS_loadPSGaidencompressedTiles(lady_eye_tiles_psgcompr, 256);
    SMS_loadSTMcompressedTileMap(6, 0, lady_tilemap_stmcompr);
}

void skull_update(void)
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
        }

        cur_stage = 2;
    }

    SMS_waitForVBlank();

    if (cur_frame > 80 && cur_stage == 2)
    {
        for (i = 0; i < 3; i++)
        {
            load_palette(palette_white, PALETTE_BACKGROUND);

            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();

            if (i == 1)
            {
                SMS_setTileatXY(14, 6, 256);
                SMS_setTileatXY(15, 6, 257);
                SMS_setTileatXY(16, 6, 257 | TILE_FLIPPED_X);
                SMS_setTileatXY(17, 6, 256 | TILE_FLIPPED_X);
                SMS_setTileatXY(14, 7, 258);
                SMS_setTileatXY(15, 7, 259);
                SMS_setTileatXY(16, 7, 259 | TILE_FLIPPED_X);
                SMS_setTileatXY(17, 7, 258 | TILE_FLIPPED_X);
                SMS_setTileatXY(14, 8, 260);
                SMS_setTileatXY(15, 8, 261);
                SMS_setTileatXY(16, 8, 261 | TILE_FLIPPED_X);
                SMS_setTileatXY(17, 8, 260 | TILE_FLIPPED_X);
                SMS_setTileatXY(14, 9, 262);
                SMS_setTileatXY(15, 9, 263);
                SMS_setTileatXY(16, 9, 263 | TILE_FLIPPED_X);
                SMS_setTileatXY(17, 9, 262 | TILE_FLIPPED_X);
            }

            load_palette(lady_palette_bin, PALETTE_BACKGROUND);

            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
        }

        cur_stage = 3;
    }

    if (cur_frame++ > 160)
    {
        for (i = 0; i < 10; i++)
        {
            fade_to_black(lady_palette_bin, i);

            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
        }

        next_scene();
    }
}

void skull_end(void)
{
    SMS_waitForVBlank();
}
