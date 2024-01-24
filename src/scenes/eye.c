#include "../assets2banks.h"
#include "../engine/palettes.h"
#include "../engine/scenes.h"
#include "../engine/tilemap.h"
#include "../libs/SMSlib.h"
#include "eye.h"

void eye_init(void)
{
    cur_frame = 192;

    SMS_waitForVBlank();
    load_palette(palette_black, PALETTE_BACKGROUND);
    clear_tilemap(0);

    SMS_mapROMBank(eye_big_palette_bin_bank);
    SMS_loadBGPalette(palette_black);
    SMS_loadSpritePalette(eye_big_palette_bin);
    SMS_loadPSGaidencompressedTiles(eye_big_tiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(4, 2, eye_big_tilemap_stmcompr);
}

void eye_update(void)
{
    SMS_waitForVBlank();
    SMS_waitForVBlank();
    SMS_setBGScrollY(cur_frame);

    uint8_t cur_row = cur_frame >> 3;
    int16_t scr_row[32];

    SMS_saveTileMapArea(0, cur_row, &scr_row, 32, 1);

    for (int i = 0; i < 32; i++)
        scr_row[i] = scr_row[i] | TILE_USE_SPRITE_PALETTE;

    SMS_loadTileMap(0, cur_row, scr_row, 32 * 2);

    if (cur_frame > 12)
        cur_frame--;
    else
        next_scene();
}

void eye_end(void)
{
    SMS_waitForVBlank();
    load_blank_tile(0);
    clear_tilemap(0);
    SMS_setBGScrollY(0);
}
