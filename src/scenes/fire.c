#include "fire.h"
#include "../assets2banks.h"
#include "../engine/palettes.h"
#include "../engine/scenes.h"
#include "../engine/vblank.h"
#include "../helpers/clear_tilemap.h"
#include "../helpers/ps_rand.h"
#include "../libs/SMSlib.h"
#include <stdlib.h>

// #define MAX(a, b) ((a) > (b)) ? (a) : (b); // Best a/b are not expressions...
#define ROW_WIDTH 32 * 2 // doubled due to 8-bit pairs, max 32
#define ROW_TOTAL 24     // max 24
#define EDGE_WIDTH 3 * 2 // doubled due to 8-bit pairs
#define FIRE_SIZE (ROW_TOTAL * ROW_WIDTH)
#define SEED_SIZE ((ROW_TOTAL + 2) * ROW_WIDTH)

// Compensate for 8-bit width by multiplying by 2
uint8_t fire[SEED_SIZE] = {0};

void fire_scene_init(void)
{
    SMS_loadPSGaidencompressedTiles(fire_grade_tiles_psgcompr, 0);
    SMS_loadBGPalette(fire_grade_palette_bin);
    SMS_loadSpritePalette(palette_black);

    clear_tilemap(0 | TILE_USE_SPRITE_PALETTE);
}

void seed_fire_tiles(void)
{
    uint8_t *fire_arr = fire + FIRE_SIZE;
    const uint8_t *fire_end = fire + SEED_SIZE,
                  *fire_edge_a = fire + FIRE_SIZE + EDGE_WIDTH,
                  *fire_edge_b = fire + FIRE_SIZE + ROW_WIDTH - EDGE_WIDTH,
                  *fire_edge_c = fire + FIRE_SIZE + ROW_WIDTH + EDGE_WIDTH,
                  *fire_edge_d = fire + SEED_SIZE - EDGE_WIDTH;

    // Generate noise across "virtual" lines
    while (fire_arr < fire_end)
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

        fire_arr += 2; // Skip every second byte
    }
}

void calc_fire_tiles_asm(void) __naked
{
    // I haven't gotten the inline assembly to work nicely in VScode yet, so the
    // extra double-slashes in the asm comments are just to fake readability

    // clang-format off
__asm
    ld  bc, #_fire
    ld  d, #0
; // while (fire_arr < fire_end)
MainFireLoop:
; // fire_tile = fire_arr[32 * 2 - 2] >> 2;
    ld  hl, #62
    add hl, bc
    ld  a, (hl)
    rra
    rra
    and a, #0x3f ; // Bit-masking to 3f (63)?
; // fire_tile += fire_arr[32 * 2] >> 2;
    inc hl
    inc hl
    ld  e, (hl)
    srl e
    srl e
    add a, e
; // fire_tile += fire_arr[32 * 2 + 2] >> 2;
    inc hl
    inc hl
    ld  e, (hl)
    srl e
    srl e
    add a, e
; // fire_tile += fire_arr[32 * 2 * 2] >> 2;
    ld  e, #62 ; // 64 - 2
    add hl, de
    ld  e, (hl)
    srl e
    srl e
    add a, e
; // if (fire_tile >= 3)
    cp  a, #0x03
    jr  C, SetFireTile
; // fire_tile -= 3;
    add a, #0xfd
SetFireTile:
; // *fire_arr = fire_tile;
    ld  (bc), a
; // fire_arr += 2;
    inc bc
    inc bc
; // }
    ; // 0x0600 (1536) is the size of the fire array not including seed rows
    ld  a, c
    sub a, #<(_fire + 0x0600) ; // This seems to be an SDCC feature for lower byte?
    ld  a, b
    sbc a, #>(_fire + 0x0600) ; // This seems to be an SDCC feature for upper byte?
    jp  C, MainFireLoop
; // Fallthrough
    ret
__endasm;
    // clang-format on
}

void fire_scene_update(void)
{
    wait_for_vblank();

    if (frame_count & 1 == 1)
    {
        seed_fire_tiles();

        // Splat the tilemap to the VDP
        SMS_VRAMmemcpy(SMS_PNTAddress, &fire, FIRE_SIZE);
        // Slower sectional copy; more efficient with smaller fire sizes
        // SMS_loadTileMapArea((32 - (ROW_WIDTH >> 1)) >> 1, 0, &fire, (ROW_WIDTH >> 1), ROW_TOTAL);
    }
    else
    {
        calc_fire_tiles_asm();
    }
}

// Transpiled to z80 assembly above
// #define FIRE_A ROW_WIDTH - 2
// #define FIRE_B ROW_WIDTH
// #define FIRE_C ROW_WIDTH + 2
// #define FIRE_X ROW_WIDTH * 2
// #define FIRE_DAMPEN 3 // lower = taller flames
// void calc_fire_tiles(void)
// {
//     uint8_t *fire_arr = fire, fire_tile;
//     const uint8_t *fire_end = fire + FIRE_SIZE;

//     //   i   <- Current row item
//     // a b c <- First row below
//     //   x   <- Second row below
//     while (fire_arr < fire_end)
//     {
//         // This may seem unnecessary in C, but it makes the generated z80
//         // assembly code muck about less. fire_arr[VAL] == *(fire_arr + VAL)
//         fire_tile = fire_arr[FIRE_A] >> 2;
//         fire_tile += fire_arr[FIRE_B] >> 2;
//         fire_tile += fire_arr[FIRE_C] >> 2;
//         fire_tile += fire_arr[FIRE_X] >> 2;

//         if (fire_tile >= FIRE_DAMPEN)
//             fire_tile -= FIRE_DAMPEN;

//         *fire_arr = fire_tile;

//         fire_arr += 2; // Skip every second byte
//     }
// }
