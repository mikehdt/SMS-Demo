#include "plasma.h"
#include "../assets2banks.h"
#include "../engine/core.h"
#include "../engine/palettes.h"
#include "../engine/scenes.h"
#include "../helpers/sintab.h"
#include "../libs/SMSlib.h"
#include <stdint.h>
#include <stdlib.h>

uint16_t plasma[SCREEN_COLUMNS * SCREEN_ROWS], buffer[SCREEN_COLUMNS * SCREEN_ROWS];
uint16_t screen_size_bytes = SCREEN_COLUMNS * SCREEN_ROWS * 2; // 2bpp

void first_plasma_scene_init(void)
{
    SMS_loadPSGaidencompressedTiles(plasma_grade_tiles_psgcompr, 0);
    SMS_loadBGPalette(plasma_grade_palette_bin);
    SMS_loadSpritePalette(palette_black);

    clear_tilemap(256 | TILE_USE_SPRITE_PALETTE);

    uint16_t x, y;

    for (x = 0; x < SCREEN_ROWS; x++)
        for (y = 0; y < SCREEN_COLUMNS; y++)
            plasma[(x * SCREEN_COLUMNS) + y] = (128 + sintab[x << 3] + 128 + sintab[y << 3]) >> 1;
}

void first_plasma_scene_update(void)
{
    uint16_t x, y, palette_shift;

    palette_shift = (frame_count << 2) & 255;

    for (x = 0; x < SCREEN_ROWS; x++)
        for (y = 0; y < SCREEN_COLUMNS; y++)
            buffer[(x * SCREEN_COLUMNS) + y] = (plasma[(x * SCREEN_COLUMNS) + y] + palette_shift) & 255;

    wait_for_vblank();

    // This will be heinously slow
    SMS_VRAMmemcpy(SMS_PNTAddress, &buffer, screen_size_bytes);
}

void plasma_scene_init(void)
{
    SMS_loadPSGaidencompressedTiles(plasma_grade_tiles_psgcompr, 0);
    SMS_loadBGPalette(plasma_grade_palette_bin);
    SMS_loadSpritePalette(palette_black);

    clear_tilemap(256 | TILE_USE_SPRITE_PALETTE);

    uint16_t x, y;
}

void plasma_scene_update(void)
{
    uint16_t x, y, palette_shift;

    wait_for_vblank();

    // This will be heinously slow
    SMS_VRAMmemcpy(SMS_PNTAddress, &buffer, screen_size_bytes);
}
