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
uint16_t SineAddsX = 8;
uint16_t SineAddsY = 8;
uint16_t SineStartsY = 8;
uint16_t SineSpeeds = 2;
uint16_t PlasmaFreqs = 2;
uint16_t CycleSpeed = 1;
uint16_t ColorPalette = 0;
uint16_t ScreenWidth = 32;
uint16_t ScreenHeight = 24;

// uint8_t RowFreq[8] = {0xfa, 0x05, 0x03, 0xfa, 0x07, 0x04, 0xfe, 0xfe};
// uint8_t ColFreq[8] = {0xfe, 0x01, 0xfe, 0x02, 0x03, 0xff, 0x02, 0x02};
// uint8_t StartAng[8] = {0x5e, 0xe8, 0xeb, 0x32, 0x69, 0x4f, 0x0a, 0x41};

uint8_t RowFreq[8] = {0x04, 0x05, 0xfc, 0x02, 0xfc, 0x03, 0x02, 0x01};
uint8_t ColFreq[8] = {0x00, 0x01, 0x03, 0xfd, 0x02, 0xfd, 0xfe, 0x00};
uint8_t StartAng[8] = {0x51, 0xa1, 0x55, 0xc1, 0x0d, 0x5a, 0xdd, 0x26};

uint16_t buffer[SCREEN_ROWS][SCREEN_COLUMNS]; // optimise to double 8-bit later
int16_t PlasmaCnts, CycleCnt, DurationCnt;

void init_buffer(void)
{
    uint8_t x, y, Phase;
    uint16_t sin_val;
    // StillFrame(x,y) = sum[n=1..8]: sin(StartAngle[n] + ColFreq[n] * x + RowFreq[n] * y)
    for (y = 0; y < SCREEN_ROWS; y++)
    {
        for (x = 0; x < SCREEN_COLUMNS; x++)
        {
            sin_val = 0;

            for (Phase = 0; Phase <= NumSinePnts; Phase++)
                sin_val += (StartAng[Phase] + (ColFreq[Phase] * x) + (RowFreq[Phase] * y));

            buffer[y][x] = sintab[sin_val >> 8] + 128;
        }
    }

    //clang-format on
}

void plasma_scene_init(void)
{
    SMS_loadPSGaidencompressedTiles(plasma_grade_tiles_psgcompr, 0);
    SMS_loadBGPalette(plasma_grade_palette_bin);
    SMS_loadSpritePalette(palette_black);

    clear_tilemap(256 | TILE_USE_SPRITE_PALETTE);

    // make_sine_table(); // found in sin_tab
    // make_speed_code(); // future :)
    // load_pattern_table(); // this is done by the PSG tiles above :)
    init_buffer(); // init first effect
}

void plasma_scene_update(void)
{
    wait_for_vblank();

    init_buffer();

    SMS_VRAMmemcpy(SMS_PNTAddress, &buffer, SCREEN_SIZE_BYTES);
}
