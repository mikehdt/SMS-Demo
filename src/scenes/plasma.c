#include "plasma.h"
#include "../assets2banks.h"
#include "../engine/globals.h"
#include "../engine/palettes.h"
#include "../engine/screen_buffer.h"
#include "../engine/update_scenes.h"
#include "../helpers/clear_tilemap.h"
#include "../helpers/memcpy_expand_byte.h"
#include "../helpers/ps_rand.h"
#include "../helpers/sintab.h"
#include "../libs/SMSlib.h"
#include <stdint.h>
#include <stdlib.h>

// This is a reverse deconstruction of:
// https://hackaday.io/project/159057-game-boards-for-rc2014/log/183324-plasma-effect-for-tms9918
//
// C is slower, for sure, but I also wanted to understand the logical
// underpinning of the effect, even if that comes at a performance hit :)

#define PLASMA_PTS 8

// These are all 0-255 numbers that get combined in weird and wonderful ways
// to reference a point in the sine table. Each of these values forms the
// configuration for how the final plasma effect looks and animates.
uint8_t sin_adds_x[PLASMA_PTS] = {0xfa, 0x05, 0x03, 0xfa, 0x07, 0x04, 0xfe, 0xfe},
        sin_adds_y[PLASMA_PTS] = {0xfe, 0x01, 0xfe, 0x02, 0x03, 0xff, 0x02, 0x02},
        sin_pts_y[PLASMA_PTS] = {0x5e, 0xe8, 0xeb, 0x32, 0x69, 0x4f, 0x0a, 0x41},
        sin_speeds[2] = {0xfe, 0xfc},
        plasma_freqs[2] = {0x06, 0x07},
        cycle_speed = 0xff;

// Stores the state of the x component of the sine values. The y complement is
// initialised to some values above. Both array values get heavily mutated.
uint8_t sin_pts_x[PLASMA_PTS] = {0x00};

uint8_t plasma_starts[SCREEN_SIZE] = {0x00};

// Init
// I(x,y) = 8/Σ/n=1 sin(Sn + Xn * x + Yn + y)
// Where x(Column), y(Row), S(sin_starts_y), X(sin_adds_x), Y(sin_adds_y)
// Upon reflection, I'm not sure the complexity is captured in that formula...
void init_buffer(void)
{
    uint16_t i, j, k;
    uint8_t plasma_value;

    // Y loop
    for (i = 0; i < SCREEN_ROWS; i++)
    {
        // Sine points Y loop
        for (j = 0; j < PLASMA_PTS; j++)
        {
            sin_pts_y[j] += sin_adds_y[j];
            sin_pts_x[j] = sin_pts_y[j];
        }

        // X loop
        for (j = 0; j < SCREEN_COLUMNS; j++)
        {
            // Sine points X loop
            for (k = 0; k < PLASMA_PTS; k++)
                sin_pts_x[k] += sin_adds_x[k];

            plasma_value = 0;

            // Sine add loop
            for (k = 0; k < PLASMA_PTS; k++)
                plasma_value += sintab[sin_pts_x[k]];

            plasma_starts[(i * SCREEN_COLUMNS) + j] = plasma_value;
        }
    }
}

// Animate
// D(n,y) = (sin(S1 * n + P1 * y) + sin(S2 * n + P2 * y)) / 2 + C * n
// Where y(Row), n(Frame), S(sin_speeds), P(plasma_freqs), C(cycle_speed)
void animate_buffer(void)
{
    uint8_t i, j,
        sin_1, sin_2,
        distortion_val,
        cur_speed = cycle_speed * frame_count,
        plasma_speed[2] = {0x00};
    uint16_t arr_offset;

    plasma_speed[0] = sin_speeds[0] * frame_count;
    plasma_speed[1] = sin_speeds[1] * frame_count;

    for (i = 0; i < SCREEN_ROWS; i++)
    {
        sin_1 = plasma_speed[0] + (plasma_freqs[0] * i);
        sin_2 = plasma_speed[1] + (plasma_freqs[1] * i);
        distortion_val = ((sintab[sin_1] + sintab[sin_2]) >> 1) + cur_speed;

        // This relies on being able to wrap-around an 8-bit integer value
        for (j = 0; j < SCREEN_COLUMNS; j++)
        {
            arr_offset = (i * SCREEN_COLUMNS) + j;
            screen_buffer[arr_offset] = plasma_starts[arr_offset] + distortion_val;
        }
    }
}

void plasma_scene_init(void)
{
    SMS_mapROMBank(plasma_grade_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(plasma_grade_tiles_psgcompr, 0);
    SMS_loadBGPalette(plasma_grade_palette_bin);
    clear_tilemap(256 | TILE_USE_SPRITE_PALETTE);

    init_buffer();

    SMS_loadSpritePalette(palette_black);
}

void plasma_scene_update(void)
{
    animate_buffer();

    SMS_waitForVBlank();
    VRAMmemcpyExpandByte(SMS_PNTAddress, &screen_buffer, SCREEN_SIZE);
}
