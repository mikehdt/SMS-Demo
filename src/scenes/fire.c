#include "fire.h"
#include "../assets2banks.h"
#include "../engine/global_constants.h"
#include "../engine/palettes.h"
#include "../engine/scenes.h"
#include "../engine/tilemap.h"
#include "../helpers/memcpy_expand_byte.h"
#include "../helpers/ps_rand.h"
#include "../helpers/screen_buffer.h"
#include "../libs/SMSlib.h"
#include <stdlib.h>

#define FIRE_SIZE (SCREEN_COLUMNS * SCREEN_ROWS)
#define SEED_SIZE (2 * SCREEN_COLUMNS)

uint8_t fire_step = 0;

void seed_fire_tiles(void)
{
    // This is a bit messy, :shrug:
    uint8_t *fire_arr = screen_buffer + FIRE_SIZE;
    const uint8_t *fire_end = screen_buffer + FIRE_SIZE + SEED_SIZE;

    // Generate noise across "virtual" lines
    do
    {
        *fire_arr = ps_rand();
    } while (++fire_arr < fire_end);
}

// ----- FOR REFERENCE -----
// #define FIRE_A SCREEN_COLUMNS - 1
// #define FIRE_B SCREEN_COLUMNS
// #define FIRE_C SCREEN_COLUMNS + 1
// #define FIRE_D SCREEN_COLUMNS * 2
// #define FIRE_DAMPEN 3 // lower = taller flames

// void calc_fire_tiles(void)
// {
//     uint8_t *fire_arr = screen_buffer, fire_tile;
//     const uint8_t *fire_end = screen_buffer + FIRE_SIZE;

//     //   x   <- Current row item
//     // a b c <- First row below
//     //   d   <- Second row below
//     while (fire_arr < fire_end)
//     {
//         // For remembering: fire_arr[VAL] same as *(fire_arr + VAL)
//         fire_tile = fire_arr[FIRE_A] >> 2;
//         fire_tile += fire_arr[FIRE_B] >> 2;
//         fire_tile += fire_arr[FIRE_C] >> 2;
//         fire_tile += fire_arr[FIRE_D] >> 2;

//         if (fire_tile >= FIRE_DAMPEN)
//             fire_tile -= FIRE_DAMPEN;

//         *fire_arr = fire_tile;

//         fire_arr++;
//     }
// }

// -----

void calc_fire_tiles_asm(void) __naked
{
    // clang-format off
    __asm
        ld  bc, #_screen_buffer
        ld  d, #0x00
    MainFireLoop:
    ; // while (fire_arr < fire_end) {
        ; // 0x0300 (768) is the size of the fire array NOT including seed rows, otherwise it'd be 0x0340
        ld  a, c
        sub a, #<(_screen_buffer + 0x0300) ; // #<(...) seems to be an SDCC feature for lower byte?
        ld  a, b
        sbc a, #>(_screen_buffer + 0x0300) ; // #>(...) seems to be an SDCC feature for upper byte?
        ret NC ; // Escape out if done
    ; // fire_tile = fire_arr[32 - 1 (FIRE_A)] >> 2;
        ld  hl, #0x1f
        add hl, bc
        ld  a, (hl)
        rrca
        rrca
        and a, #0x3f ; // Bit-masking to 3f (63)
    ; // fire_tile += fire_arr[32 (FIRE_B)] >> 2;
        inc hl
        ld  e, (hl)
        srl e
        srl e
        add a, e
    ; // fire_tile += fire_arr[32 + 1 (FIRE_C)] >> 2;
        inc hl
        ld  e, (hl)
        srl e
        srl e
        add a, e
    ; // fire_tile += fire_arr[32 * 2 (FIRE_D)] >> 2;
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
    ; // }
        jp MainFireLoop
    __endasm;
    // clang-format on
}

void fire_init(void)
{
    SMS_displayOff();
    SMS_waitForVBlank();
    SMS_mapROMBank(fire_grade_tiles_psgcompr_bank);
    // Can I generate these tiles dynamically?
    SMS_loadPSGaidencompressedTiles(fire_grade_tiles_psgcompr, 0);
    SMS_loadBGPalette(fire_grade_palette_bin);
    SMS_loadSpritePalette(palette_black);

    clear_tilemap(0);

    SMS_displayOn();
}

void fire_update(void)
{
    SMS_waitForVBlank();

    seed_fire_tiles();
    // calc_fire_tiles();
    calc_fire_tiles_asm();

    // Splat the tilemap to the VDP
    VRAMmemcpyExpandByte(SMS_PNTAddress, &screen_buffer, FIRE_SIZE); // + SEED_SIZE for visual seed debug
    // Slower sectional copy; more efficient with smaller fire sizes
    // SMS_loadTileMapArea((32 - ROW_WIDTH) >> 1, 0, &screen_buffer, ROW_WIDTH, ROW_TOTAL);

    if (cur_frame++ > 80)
    {
        fade_to_black(fire_grade_palette_bin, fire_step);

        if (fire_step++ > 9)
        {
            fire_step = 0;
            next_scene();
        }
    }
}

void fire_end(void)
{
    SMS_displayOff();
    SMS_waitForVBlank();

    clear_screen_buffer();
    clear_tilemap(0);

    SMS_displayOn();
}
