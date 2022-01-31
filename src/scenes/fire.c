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

uint16_t aVal, bVal, cVal, xVal; // Faux row value bake

uint16_t fire_idx;

// Y-coordinate first because we use horizontal scanlines
int fire[192]; // Not sure why can't use offscreen_size

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
    aVal = 11;
    bVal = 12;
    cVal = 13;
    xVal = 24;

    while (fire_idx < 168)
    {
        // clang-format off
        __asm
            // insert brain here
        __endasm;
        // clang-format on

        // This calculation _does_ cause int wrap-around, but would need a fast
        // way to counter this without an if condition...
        fire[fire_idx] = ((fire[aVal++] + fire[bVal++] + fire[cVal++] + fire[xVal++]) >> 2) - 6;

        fire_idx++;
    }

    fire_idx = 168;

    // Generate noise across "virtual" lines
    while (fire_idx < 192)
    {
        if (fire_idx < 170 || (fire_idx >= 178 && fire_idx < 182) || fire_idx >= 190)
            fire[fire_idx] = 0;
        else
            fire[fire_idx] = rand() & 255;

        fire_idx++;
    }

    // Dump the tilemap to the VDP - use offscreen_size for debug
    // SMS_VRAMmemcpy(SMS_PNTAddress, &fire, screen_size * 2); // 2 bytes per ea
    SMS_loadTileMapArea(10, 0, &fire, 12, 14);
}
