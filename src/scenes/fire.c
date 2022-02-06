#include "fire.h"
#include "../assets2banks.h"
#include "../engine/core.h"
#include "../engine/palettes.h"
#include "../engine/scenes.h"
#include "../libs/SMSlib.h"
#include <stdlib.h>

// #define MAX(a, b) ((a) > (b)) ? (a) : (b); // Best a/b are not expressions...
#define ROW_WIDTH 32 * 2 // doubled due to 8-bit pairs, max 32
#define ROW_TOTAL 16     // max 24
#define EDGE_WIDTH 6
#define FIRE_A ROW_WIDTH - 2
#define FIRE_B ROW_WIDTH
#define FIRE_C ROW_WIDTH + 2
#define FIRE_X ROW_WIDTH * 2
#define FIRE_DAMPEN 6 // lower = taller flames
#define FIRE_SIZE (ROW_TOTAL * ROW_WIDTH)
#define SEED_SIZE ((ROW_TOTAL + 2) * ROW_WIDTH)
uint16_t fire_idx, test;
uint8_t SEED = 0;
uint16_t RandomSeed = 0;

// Compensate for 8-bit width by multiplying by 2
uint8_t fire[SEED_SIZE] = {0};

void fire_scene_init(void)
{
    SMS_loadPSGaidencompressedTiles(fire_grade_tiles_psgcompr, 0);
    SMS_loadBGPalette(fire_grade_palette_bin);
    SMS_loadSpritePalette(palette_black);

    clear_tilemap(0 | TILE_USE_SPRITE_PALETTE);
}

// Candidate to move to its own utility file
char ps_rand() __naked
{
    // Code adapted for SDCC from Phantasy Star's PRNG as documented at
    // https://www.smspower.org/Development/RandomNumberGenerator
    // clang-format off
__asm
GetRandomNumber:
    ld      hl, (_RandomSeed)
    ld      a, h        ; get high byte
    rrca                ; rotate right by 2
    rrca
    xor     h           ; xor with original
    rrca                ; rotate right by 1
    xor     l           ; xor with low byte
    rrca                ; rotate right by 4
    rrca
    rrca
    rrca
    xor     l           ; xor again
    rra                 ; rotate right by 1 through carry
    adc     hl, hl      ; add RandomSeed to itself
    jr      nz, RandomContinue
    ld      hl, #0x733c ; if last xor resulted in zero then reseed rng
RandomContinue:
    ld      a, r        ; r = refresh register = semi-random number
    xor     l           ; xor with l which is fairly random
    ld      (_RandomSeed), hl
    ld      l, a        ; move a into l to return a char back to the caller
    ret
__endasm;
    // clang-format on
}

void fire_scene_update(void)
{
    if (frame_count & 1 == 1)
    {
        wait_for_vblank();

        fire_idx = FIRE_SIZE;

        // Generate noise across "virtual" lines
        while (fire_idx < SEED_SIZE)
        {
            // Blank the sides across the two noise rows
            if (fire_idx < FIRE_SIZE + EDGE_WIDTH || (fire_idx >= FIRE_SIZE + ROW_WIDTH - EDGE_WIDTH && fire_idx < FIRE_SIZE + ROW_WIDTH + EDGE_WIDTH) || fire_idx >= SEED_SIZE - EDGE_WIDTH)
                fire[fire_idx] = 0;
            else
                fire[fire_idx] = ps_rand();

            fire_idx += 2; // Skip every second byte
        }

        // Splat the tilemap to the VDP
        SMS_VRAMmemcpy(SMS_PNTAddress, &fire, FIRE_SIZE);
        // Slower sectional copy; more efficient with smaller fire sizes
        // SMS_loadTileMapArea((32 - (ROW_WIDTH >> 1)) >> 1, 0, &fire, (ROW_WIDTH >> 1), ROW_TOTAL);
    }
    else
    {
        uint8_t fire_tile;
        fire_idx = 0;

        //   i   <- Current row item
        // a b c <- First row below
        //   x   <- Second row below
        while (fire_idx < FIRE_SIZE)
        {
            // This may seem unnecessary in C, but it makes the generated z80
            // assembly code muck about less
            fire_tile = *(&fire[fire_idx] + FIRE_A) >> 2;
            fire_tile += *(&fire[fire_idx] + FIRE_B) >> 2;
            fire_tile += *(&fire[fire_idx] + FIRE_C) >> 2;
            fire_tile += *(&fire[fire_idx] + FIRE_X) >> 2;

            if (fire_tile > FIRE_DAMPEN + 1)
                fire_tile -= FIRE_DAMPEN;

            fire[fire_idx] = fire_tile;

            fire_idx += 2; // Skip every second byte
        }
    }
}
