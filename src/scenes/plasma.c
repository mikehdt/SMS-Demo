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
// which itself is a Z80-compatible interpretation of Cruzer/CML's C64 routine
//
// Compiled C is slower, for sure, but I also wanted to understand the logical
// underpinning of the effect, even if that comes at a performance hit :)

#define PLASMA_PTS 8

// These are all 0-255 numbers that get combined in weird and wonderful ways
// to reference a point in the sine table. Each of these values forms the
// configuration for how the final plasma effect looks and animates.
uint8_t sin_config[PLASMA_PTS * 3] = {0xfa, 0x05, 0x03, 0xfa, 0x07, 0x04, 0xfe, 0xfe,  // sin_adds_x
                                      0xfe, 0x01, 0xfe, 0x02, 0x03, 0xff, 0x02, 0x02,  // sin_adds_y
                                      0x5e, 0xe8, 0xeb, 0x32, 0x69, 0x4f, 0x0a, 0x41}; // sin_starts_y
uint8_t sin_speeds_1 = 0xfe,
        sin_speeds_2 = 0xfc,
        plasma_freqs_1 = 0x06,
        plasma_freqs_2 = 0x07,
        cycle_speed = 0xff;

// Stores the state of the x component of the sine values. The y complement is
// initialised to some values above. Both array values get heavily mutated.
uint8_t sin_pts_x[PLASMA_PTS] = {0x00},
        sin_pts_y[PLASMA_PTS] = {0x00};

uint8_t plasma_starts[SCREEN_SIZE] = {0x00};

// Init
// I(x,y) = 8/Σ/n=1 sin(Sn + Xn * x + Yn + y)
// Where x(Column), y(Row), S(sin_starts_y), X(sin_adds_x), Y(sin_adds_y)
// Upon reflection, I'm not sure the complexity is captured in that formula...
void init_buffer(void)
{
    uint8_t *sin_starts_y_arr = sin_config + (PLASMA_PTS * 2),
            *sin_starts_y_end = sin_config + (PLASMA_PTS * 3),
            *sin_pts_x_arr = sin_pts_x,
            *sin_pts_y_arr = sin_pts_y,
            *sin_adds_x_arr = sin_config,
            *sin_adds_y_arr = sin_config + PLASMA_PTS,
            *plasma_arr = plasma_starts,
            *plasma_end = plasma_starts + SCREEN_SIZE,
            *plasma_loop,
            *plasma_offset_loop;

    // Calc plasma starting Y values
    do
    {
        *sin_pts_y_arr = *sin_starts_y_arr;

        sin_pts_y_arr++;
        sin_starts_y_arr++;
    } while (sin_starts_y_arr < sin_starts_y_end);

    // Y loop
    do
    {
        // Reset offsets
        sin_adds_y_arr = sin_config + PLASMA_PTS;
        sin_pts_x_arr = sin_pts_x;
        sin_pts_y_arr = sin_pts_y;
        plasma_loop = sin_pts_y + PLASMA_PTS;

        // Sine points Y loop
        do
        {
            *sin_pts_y_arr += *sin_adds_y_arr;
            *sin_pts_x_arr = *sin_pts_y_arr;

            sin_pts_x_arr++;
            sin_pts_y_arr++;
            sin_adds_y_arr++;
        } while (sin_pts_y_arr < plasma_loop);

        // X loop
        plasma_loop = plasma_arr + SCREEN_COLUMNS;

        do
        {
            sin_pts_x_arr = sin_pts_x;
            sin_adds_x_arr = sin_config;
            plasma_offset_loop = sin_pts_x + PLASMA_PTS;

            // Sine points X loop
            do
            {
                *sin_pts_x_arr += *sin_adds_x_arr;

                sin_pts_x_arr++;
                sin_adds_x_arr++;
            } while (sin_pts_x_arr < plasma_offset_loop);

            // Reset offset
            sin_pts_x_arr = sin_pts_x;

            *plasma_arr = 0;

            // Sine add loop
            do
            {
                *plasma_arr += sintab[*sin_pts_x_arr];
                sin_pts_x_arr++;
            } while (sin_pts_x_arr < plasma_offset_loop);

            plasma_arr++;
        } while (plasma_arr < plasma_loop);
    } while (plasma_arr < plasma_end);
}

// Animate
// D(n,y) = (sin(S1 * n + P1 * y) + sin(S2 * n + P2 * y)) / 2 + C * n
// Where y(Row), n(Frame), S(sin_speeds), P(plasma_freqs), C(cycle_speed)
void animate_buffer(void)
{
    uint8_t row_count = 0,
            col_count,
            sin_1, sin_2,
            distortion_val,
            *plasma_arr = plasma_starts,
            *buffer_arr = screen_buffer,
            *buffer_end = screen_buffer + SCREEN_SIZE;
    const uint8_t cur_speed = cycle_speed * frame_count,
                  plasma_speed_1 = sin_speeds_1 * frame_count,
                  plasma_speed_2 = sin_speeds_2 * frame_count;

    do
    {
        col_count = 0;

        // For some reason, the code goes sideways if these are collapsed into
        // the distortion_val formula below...
        sin_1 = plasma_speed_1 + (plasma_freqs_1 * row_count);
        sin_2 = plasma_speed_2 + (plasma_freqs_2 * row_count);
        distortion_val = (sintab[sin_1] >> 1) + (sintab[sin_2] >> 1) + cur_speed;

        // This relies on being able to wrap-around an 8-bit integer value
        do
        {
            *buffer_arr = *plasma_arr + distortion_val;

            plasma_arr++;
            buffer_arr++;
        } while (++col_count < SCREEN_COLUMNS);
    } while (++row_count < SCREEN_ROWS);
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
