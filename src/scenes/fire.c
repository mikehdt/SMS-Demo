#include "fire.h"
#include "../assets2banks.h"
#include "../engine/core.h"
#include "../engine/palettes.h"
#include "../engine/scenes.h"
#include "../libs/SMSlib.h"
#include <stdlib.h>

// #define MAX(a, b) ((a) > (b)) ? (a) : (b); // Best a/b are not expressions...

// const uint16_t screen_size = SCREEN_COLUMNS * 24;
// const uint16_t offscreen_size = SCREEN_COLUMNS * 26;

#define ROW_WIDTH 12
#define ROW_TOTAL 16
uint16_t aVal, bVal, cVal, xVal; // Faux row value bake
uint16_t fire_idx;

// Y-coordinate first because we use horizontal scanlines
int fire[(ROW_TOTAL + 2) * ROW_TOTAL]; // Not sure why can't use offscreen_size

void fire_scene_init(void)
{
    SMS_loadPSGaidencompressedTiles(fire_grade_tiles_psgcompr, 0);
    SMS_loadBGPalette(fire_grade_palette_bin);
    SMS_loadSpritePalette(palette_black);

    clear_tilemap(0 | TILE_USE_SPRITE_PALETTE);
}

void fire_scene_update(void)
{
    wait_for_vblank();

    //   i   <- Current row item
    // a b c <- First row below
    //   x   <- Second row below
    fire_idx = 0;
    aVal = ROW_WIDTH - 1;
    bVal = ROW_WIDTH;
    cVal = ROW_WIDTH + 1;
    xVal = ROW_WIDTH * 2;

    while (fire_idx < ROW_TOTAL * ROW_WIDTH)
    {
        // clang-format off
        __asm
            // insert brain here
        __endasm;
        // clang-format on

        // This calculation _does_ cause int wrap-around, but would need a fast
        // way to counter this without an if condition...
        fire[fire_idx] = ((fire[aVal++] + fire[bVal++] + fire[cVal++] + fire[xVal++]) >> 2) - 4;

        fire_idx++;
    }

    fire_idx = ROW_TOTAL * ROW_WIDTH;

    // Generate noise across "virtual" lines
    while (fire_idx < (ROW_TOTAL + 2) * ROW_WIDTH)
    {
        // This is messy, just ignore it for now :3
        if (fire_idx < (ROW_TOTAL * ROW_WIDTH + 2) || (fire_idx >= ((ROW_TOTAL + 1) * ROW_WIDTH - 2) && fire_idx < ((ROW_TOTAL + 1) * ROW_WIDTH + 2)) || fire_idx >= ((ROW_TOTAL + 2) * ROW_WIDTH - 2))
            fire[fire_idx] = 0;
        else
            fire[fire_idx] = rand() & 255;

        fire_idx++;
    }

    // Dump the tilemap to the VDP - use offscreen_size for debug
    // SMS_VRAMmemcpy(SMS_PNTAddress, &fire, screen_size * 2); // 2 bytes per ea
    SMS_loadTileMapArea(10, 0, &fire, ROW_WIDTH, ROW_TOTAL);
}
