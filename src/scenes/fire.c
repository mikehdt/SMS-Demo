#include "fire.h"
#include "../assets2banks.h"
#include "../engine/palettes.h"
#include "../engine/screen_buffer.h"
#include "../engine/tilemap.h"
#include "../engine/update_scenes.h"
#include "../helpers/memcpy_expand_byte.h"
#include "../helpers/ps_rand.h"
#include "../libs/SMSlib.h"
#include <stdlib.h>

// #define MAX(a, b) ((a) > (b)) ? (a) : (b); // Best a/b are not expressions...
#define ROW_WIDTH 32 // max 32
#define ROW_TOTAL 24 // max 24
#define EDGE_WIDTH 3
#define FIRE_SIZE (ROW_TOTAL * ROW_WIDTH)
#define SEED_SIZE ((ROW_TOTAL + 2) * ROW_WIDTH)

void fire_scene_init(void)
{
    SMS_mapROMBank(fire_grade_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(fire_grade_tiles_psgcompr, 0);
    SMS_loadBGPalette(fire_grade_palette_bin);
    SMS_loadSpritePalette(palette_black);

    clear_tilemap(0 | TILE_USE_SPRITE_PALETTE);
}

void seed_fire_tiles(void)
{
    // This is a bit messy, :shrug:
    uint8_t *fire_arr = screen_buffer + FIRE_SIZE;
    const uint8_t *fire_end = screen_buffer + SEED_SIZE,
                  *fire_edge_a = screen_buffer + FIRE_SIZE + EDGE_WIDTH,
                  *fire_edge_b = screen_buffer + FIRE_SIZE + ROW_WIDTH - EDGE_WIDTH,
                  *fire_edge_c = screen_buffer + FIRE_SIZE + ROW_WIDTH + EDGE_WIDTH,
                  *fire_edge_d = screen_buffer + SEED_SIZE - EDGE_WIDTH;

    // Generate noise across "virtual" lines
    do
    {
        // Blank the sides across the two noise rows
        if ((fire_arr < fire_edge_a) ||
            (fire_arr >= fire_edge_b && fire_arr < fire_edge_c) ||
            (fire_arr >= fire_edge_d))
        {
            *fire_arr = 0;
        }
        else
        {
            *fire_arr = ps_rand();

            if (*fire_arr < 32)
                *fire_arr = 32;
            else if (*fire_arr > 192)
                *fire_arr = 255;
        }

        fire_arr++;
    } while (fire_arr < fire_end);
}

// ----- TO BE OPTIMISED -----
#define FIRE_A ROW_WIDTH - 1
#define FIRE_B ROW_WIDTH
#define FIRE_C ROW_WIDTH + 1
#define FIRE_X ROW_WIDTH * 2
#define FIRE_DAMPEN 3 // lower = taller flames
void calc_fire_tiles(void)
{
    uint8_t *fire_arr = screen_buffer, fire_tile;
    const uint8_t *fire_end = screen_buffer + FIRE_SIZE;

    //   i   <- Current row item
    // a b c <- First row below
    //   x   <- Second row below
    while (fire_arr < fire_end)
    {
        // For memory: fire_arr[VAL] same as *(fire_arr + VAL)
        fire_tile = fire_arr[FIRE_A] >> 2;
        fire_tile += fire_arr[FIRE_B] >> 2;
        fire_tile += fire_arr[FIRE_C] >> 2;
        fire_tile += fire_arr[FIRE_X] >> 2;

        if (fire_tile >= FIRE_DAMPEN)
            fire_tile -= FIRE_DAMPEN;

        *fire_arr = fire_tile;

        fire_arr++;
    }
}
// -----

void fire_scene_update(void)
{
    seed_fire_tiles();
    calc_fire_tiles();

    SMS_waitForVBlank();

    // Splat the tilemap to the VDP
    VRAMmemcpyExpandByte(SMS_PNTAddress, &screen_buffer, FIRE_SIZE);
    // Slower sectional copy; more efficient with smaller fire sizes
    // SMS_loadTileMapArea((32 - ROW_WIDTH) >> 1, 0, &screen_buffer, ROW_WIDTH, ROW_TOTAL);
}

// SDCC 4.1.0 assembly optimisation for reference:
/*
void calc_fire_tiles_asm(void) __naked
{
    // I haven't gotten the inline assembly to work nicely in VScode yet, so the
    // extra double-slashes in the asm comments are just to fake readability

    // TODO: Investigate possible register thwacking, maybe need to play nicer.

    // clang-format off
__asm
    ld  bc, #_screen_buffer
    ld  d, #0x00
; // do {
MainFireLoop:
; // fire_tile = fire_arr[32 - 1] >> 2;
    ld  hl, #0x1f
    add hl, bc
    ld  a, (hl)
    rra
    rra
    and a, #0x3f ; // Bit-masking to 3f (63)
; // fire_tile += fire_arr[32] >> 2;
    inc hl
    ld  e, (hl)
    srl e
    srl e
    add a, e
; // fire_tile += fire_arr[32 + 1] >> 2;
    inc hl
    ld  e, (hl)
    srl e
    srl e
    add a, e
; // fire_tile += fire_arr[32 * 2] >> 2;
    ld  e, #0x1f ; // 32 - 1, because we're at off by one from the previous row
    add hl, de
    ld  e, (hl)
    srl e
    srl e
    add a, e
; // if (fire_tile >= 3)
    cp  a, #0x03
    jr  C, SetFireTile
; // fire_tile -= 3;
    sub a, #0x03
SetFireTile:
; // *fire_arr = fire_tile;
    ld  (bc), a
; // fire_arr++;
    inc bc
; // } while (fire_arr < fire_end);
    ; // 0x0300 (768) is the size of the fire array not including seed rows
    ld  a, c
    sub a, #<(_screen_buffer + 0x0300) ; // This seems to be an SDCC feature for lower byte?
    ld  a, b
    sbc a, #>(_screen_buffer + 0x0300) ; // This seems to be an SDCC feature for upper byte?
    jp  C, MainFireLoop
; // Fallthrough
    ret
__endasm;
    // clang-format on
}
*/
