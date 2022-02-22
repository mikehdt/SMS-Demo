#include "plasma.h"
#include "../assets2banks.h"
#include "../engine/globals.h"
#include "../engine/palettes.h"
#include "../engine/scenes.h"
#include "../engine/vblank.h"
#include "../helpers/clear_tilemap.h"
#include "../helpers/ps_rand.h"
#include "../helpers/sintab.h"
#include "../libs/SMSlib.h"
#include <stdint.h>
#include <stdlib.h>

// uint16_t plasma[SCREEN_COLUMNS * SCREEN_ROWS],
//     buffer[SCREEN_COLUMNS * SCREEN_ROWS];
#define SCREEN_SIZE_BYTES (SCREEN_COLUMNS * SCREEN_ROWS * 2) // 2bpp

void first_plasma_scene_init(void)
{
    // SMS_loadPSGaidencompressedTiles(plasma_grade_tiles_psgcompr, 0);
    // SMS_loadBGPalette(plasma_grade_palette_bin);
    // SMS_loadSpritePalette(palette_black);

    // clear_tilemap(256 | TILE_USE_SPRITE_PALETTE);

    // uint16_t x, y;

    // for (x = 0; x < SCREEN_ROWS; x++)
    //     for (y = 0; y < SCREEN_COLUMNS; y++)
    //         plasma[(x * SCREEN_COLUMNS) + y] = (128 + sintab[x << 3] + 128 + sintab[y << 3]) >> 1;
}

void first_plasma_scene_update(void)
{
    // uint16_t x, y, palette_shift;

    // palette_shift = (frame_count << 2) & 255;

    // for (x = 0; x < SCREEN_ROWS; x++)
    //     for (y = 0; y < SCREEN_COLUMNS; y++)
    //         buffer[(x * SCREEN_COLUMNS) + y] = (plasma[(x * SCREEN_COLUMNS) + y] + palette_shift) & 255;

    // wait_for_vblank();

    // // This will be heinously slow
    // SMS_VRAMmemcpy(SMS_PNTAddress, &buffer, screen_size_bytes);
}

//-----

uint16_t NumSinePnts = 8;
uint16_t ColorPalette = 0; // This can be any colour palette
uint16_t ScreenWidth = 32;
uint16_t ScreenHeight = 24;

uint8_t SineAddsX[8] = {0xfa, 0x05, 0x03, 0xfa, 0x07, 0x04, 0xfe, 0xfe};
uint8_t SineAddsY[8] = {0xfe, 0x01, 0xfe, 0x02, 0x03, 0xff, 0x02, 0x02};
uint8_t SineStartsY[8] = {0x5e, 0xe8, 0xeb, 0x32, 0x69, 0x4f, 0x0a, 0x41};
uint8_t SineSpeeds[2] = {0xfe, 0xfc};
uint8_t PlasmaFreqs[2] = {0x06, 0x07};
uint8_t CycleSpeed = 0xff;

uint16_t buffer[SCREEN_ROWS][SCREEN_COLUMNS]; // optimise to double 8-bit later
uint16_t screen[SCREEN_ROWS][SCREEN_COLUMNS]; // optimise to double 8-bit later
uint16_t PlasmaCnts, CycleCnt, DurationCnt;

// Init
// I(x,y) = 8/Σ/n=1 sin(Sn + Xn * x + Yn + y)
// For each Column(x) of Row(y), where S = SinStartsY, X = SinAddsX, Y = SinAddsY
void init_buffer(void)
{
    uint8_t x, y, Phase, sin_val; // Are we relying on sin_val / sintab_lookup overflowing?
    uint16_t sintab_lookup;

    for (y = 0; y < SCREEN_ROWS; y++)
    {
        for (x = 0; x < SCREEN_COLUMNS; x++)
        {
            sin_val = 0;

            for (Phase = 0; Phase <= NumSinePnts; Phase++)
            {
                sintab_lookup = (SineStartsY[Phase] + (SineAddsX[Phase] * x) + (SineAddsY[Phase] * y)) >> 6;
                sin_val += sintab[sintab_lookup] + 128;
            }

            buffer[y][x] = sin_val;
        }
    }
}

// Animate
// D(n,y) = 1/2 * (sin(S1 * n + P1 * y) + sin(S2 * n + P2 * y)) + C * n
// For each Row(y) of Frame(n), where S = SineSpeeds, P = PlasmaFreqs, C = CycleSpeed
void animate_buffer(void)
{
    uint8_t x, y;
    uint16_t sintab_lookup_a, sintab_lookup_b, sintab_lookup_c;

    for (y = 0; y < SCREEN_ROWS; y++)
    {
        // This code is cursed
        sintab_lookup_a = (SineSpeeds[0] * CycleCnt) + (PlasmaFreqs[0] * y);
        sintab_lookup_b = (SineSpeeds[1] * CycleCnt) + (PlasmaFreqs[1] * y);
        sintab_lookup_c = (((sintab[sintab_lookup_a] + 128) + (sintab[sintab_lookup_b] + 128)) >> 1) + (8 * CycleCnt);

        for (x = 0; x < SCREEN_COLUMNS; x++)
        {
            screen[y][x] = (buffer[y][x] + sintab_lookup_c) & 255;
        }
    }
}

void plasma_scene_init(void)
{
    SMS_mapROMBank(plasma_grade_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(plasma_grade_tiles_psgcompr, 0);
    SMS_loadBGPalette(plasma_grade_palette_bin);
    SMS_loadSpritePalette(palette_black);

    clear_tilemap(256 | TILE_USE_SPRITE_PALETTE);

    // make_sine_table(); // found in sin_tab
    // make_speed_code(); // future :)
    // load_pattern_table(); // this is done by the PSG tiles above :)
    init_buffer(); // init first effect

    CycleCnt = 0;
}

void plasma_scene_update(void)
{
    wait_for_vblank();

    animate_buffer();

    SMS_VRAMmemcpy(SMS_PNTAddress, &screen, SCREEN_SIZE_BYTES);

    CycleCnt++;
}
