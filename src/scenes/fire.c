#include "fire.h"
#include "../assets2banks.h"
#include "../engine/core.h"
#include "../engine/scenes.h"
#include "../libs/SMSlib.h"
#include <stdlib.h>

// #define MAX(a, b) ((a) > (b)) ? (a) : (b); // Best a/b are not expressions...

const uint16_t screen_size = SCREEN_COLUMNS * 24;
const uint16_t offscreen_size = SCREEN_COLUMNS * 26;

uint16_t aVal = 31, bVal = 32, cVal = 33, xVal = 64;

uint16_t fire_idx = 0;

// Y-coordinate first because we use horizontal scanlines
int fire[SCREEN_COLUMNS * 26]; // Not sure why can't use offscreen_size

void fire_scene_init(void)
{
    SMS_loadPSGaidencompressedTiles(noise_grade_tiles_psgcompr, 0);
    SMS_loadBGPalette(noise_grade_palette_bin);

    clear_tilemap(256 | TILE_USE_SPRITE_PALETTE);
}

void fire_scene_update(void)
{
    wait_for_vblank();

    //   i   <- Current row item
    // a b c <- First row below
    //   x   <- Second row below
    while (fire_idx < screen_size)
    {
        fire[fire_idx] = ((fire[fire_idx + aVal] + fire[fire_idx + bVal] + fire[fire_idx + cVal] + fire[fire_idx + xVal]) >> 2) - 3;
        fire_idx++;
    }

    fire_idx = screen_size;

    // Generate noise across "virtual" lines
    while (fire_idx < offscreen_size)
    {
        fire[fire_idx] = rand() & 255;
        fire_idx++;
    }

    fire_idx = 0;

    // Dump the tilemap to the VDP - use offscreen_size for debug
    SMS_VRAMmemcpy(SMS_PNTAddress, &fire, offscreen_size * 2); // 2 bytes per ea
}
