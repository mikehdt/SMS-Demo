#include "sineline.h"
#include "../assets2banks.h" // Generated with the assets task
#include "../engine/globals.h"
#include "../engine/tilemap.h"
#include "../engine/update_scenes.h"
#include "../libs/SMSlib.h"
#include <stdint.h>

uint16_t sineline[] = {
    0, 15, 31, 45,
    0, 0, 32, 46,
    0, 0, 14, 47,
    0, 0, 0, 48,
    0, 0, 0, 49,
    0, 0, 1, 50,
    0, 0, 33, 51,
    0, 16, 34, 52,
    0, 17, 35, 53,
    0, 18, 36, 54,
    1, 19, 37, 15 | TILE_FLIPPED_Y,
    2, 20, 38, 0,
    3, 21, 39, 0,
    4, 22, 0, 0,
    5, 23, 0, 0,
    6, 15 | TILE_FLIPPED_Y, 0, 0,
    7, 0, 0, 0,
    8, 0, 0, 0,
    9, 16 | TILE_FLIPPED_Y, 0, 0,
    10, 24, 0, 0,
    11, 25, 0, 0,
    12, 26, 40, 0,
    13, 27, 41, 0,
    14, 28, 42, 16 | TILE_FLIPPED_Y,
    0, 29, 43, 55,
    0, 30, 44, 56};

uint16_t sineline_ptr;

void sineline_scene_init(void)
{
    SMS_mapROMBank(small_sine_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(small_sine_tiles_psgcompr, 0);
    SMS_loadBGPalette(small_sine_palette_bin);
    sineline_ptr = 0;

    clear_tilemap(0);

    SMS_initSprites();
    SMS_setSpriteMode(SPRITEMODE_ZOOMED);

    SMS_mapROMBank(spheres_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(spheres_tiles_psgcompr, 57);
    SMS_loadSpritePalette(spheres_palette_bin);

    for (uint8_t i = 0; i < 8; i++)
        SMS_addSprite(8 + (i * 32), 72, 60);

    SMS_copySpritestoSAT();
}

void fill_line_tilemap(uint16_t row, uint16_t tile) // Must be an int, not a uint_8t or such
{
    SMS_VRAMmemsetW(XYtoADDR(0, row + 8), tile, SCREEN_COLUMNS * 2); // 2 bytes / tile
}

void sineline_scene_update(void)
{
    SMS_waitForVBlank();

    if (frame_count % 2 == 0)
    {
        return;
    }

    uint8_t i;
    uint16_t priority = (sineline_ptr > 3 && sineline_ptr < 15) ? 0 : TILE_PRIORITY;

    for (i = 0; i < 4; i++)
        fill_line_tilemap(i, sineline[i + (sineline_ptr << 2)] | priority);

    if (sineline_ptr++ > 24)
        sineline_ptr = 0;
}

void sineline_scene_end(void)
{
    SMS_waitForVBlank();

    SMS_initSprites();
    SMS_setSpriteMode(SPRITEMODE_NORMAL);
}
