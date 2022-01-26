#include "fire.h"
#include "../assets2banks.h"
#include "../engine/core.h"
#include "../engine/scenes.h"
#include "../libs/SMSlib.h"
#include <stdlib.h>

// #define MAX(a, b) ((a) > (b)) ? (a) : (b); // Best a/b are not expressions...

const uint16_t screenDims = SCREEN_COLUMNS * 24;
const uint16_t offscreenDims = SCREEN_COLUMNS * 26;

uint16_t aVal = SCREEN_COLUMNS - 1,
         bVal = SCREEN_COLUMNS,
         cVal = SCREEN_COLUMNS + 1,
         xVal = SCREEN_COLUMNS * 2;

// // Y-coordinate first because we use horizontal scanlines
int fire[SCREEN_COLUMNS * 26]; // Not sure why can't use offscreenDims

void fire_scene_init(void)
{
    SMS_loadPSGaidencompressedTiles(noise_grade_tiles_psgcompr, 0);
    SMS_loadBGPalette(noise_grade_palette_bin);

    clear_tilemap(256 | TILE_USE_SPRITE_PALETTE);
}

void fire_scene_update(void)
{
    //   i   <- Current row item
    // a b c <- first row below
    //   x   <- second row below
    uint16_t i = 0;

    while (i < screenDims)
    {
        fire[i] = ((fire[i + aVal] + fire[i + bVal] + fire[i + cVal] + fire[i + xVal]) >> 2) - 12;
        i++;
    }

    i = screenDims;

    // Generate noise across "virtual" lines
    while (i < offscreenDims)
    {
        fire[i] = rand() & 255;
        i++;
    }

    // Dump the tilemap to the VDP
    SMS_VRAMmemcpy(XYtoADDR(0, 0), fire, screenDims * 2); // 2 bytes per ea

    wait_for_frame();
}
