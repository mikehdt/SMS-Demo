#include "plasma.h"
#include "../assets2banks.h"
#include "../engine/clear_tilemap.h"
#include "../engine/globals.h"
#include "../engine/palettes.h"
#include "../engine/screen_buffer.h"
#include "../engine/update_scenes.h"
#include "../helpers/memcpy_expand_byte.h"
#include "../helpers/ps_rand.h"
#include "../helpers/sintab.h"
#include "../libs/SMSlib.h"
#include <stdint.h>
#include <stdlib.h>

// This is a reverse deconstruction of the fantastic:
// https://hackaday.io/project/159057-game-boards-for-rc2014/log/183324-plasma-effect-for-tms9918
// which itself is a Z80 interpretation of Cruzer/CML's smart C64 routine
//
// Compiled C is slower, for sure, but I also wanted to understand the logical
// underpinning of the effect, even if that comes at a performance hit :)

#define PLASMA_PTS 8

// These are all 0-255 numbers that get combined in weird and wonderful ways
// to reference a point in the sine table. Each of these values forms the
// configuration for how the final plasma effect looks and animates.
uint8_t sin_starts_y[PLASMA_PTS] = {0x5e, 0xe8, 0xeb, 0x32, 0x69, 0x4f, 0x0a, 0x41},
        sin_adds_x[PLASMA_PTS] = {0xfa, 0x05, 0x03, 0xfa, 0x07, 0x04, 0xfe, 0xfe},
        sin_adds_y[PLASMA_PTS] = {0xfe, 0x01, 0xfe, 0x02, 0x03, 0xff, 0x02, 0x02};
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
void init_buffer(void) __naked
{
    // clang-format off
__asm
InitSinPtsY:
    ld  hl, #_sin_starts_y
    ld  de, #_sin_pts_y
    ld  bc, #PLASMA_PTS
    ldir    ; // ld (de), (hl) then decrement bc, repeat until bc is 0

    ld  hl, #_plasma_starts     ; // used later on after adding sine loop values
    ld  c, #SCREEN_ROWS

YLoop:
    exx     ; // use bc', de', hl'
    ld  bc, #_sin_pts_y
    ld  hl, #_sin_adds_y
    ld  de, #_sin_pts_x
    exx     ; // use bc, de, hl

    ld  d, #PLASMA_PTS  ; // paired with #SCREEN_ROWS above

SinPtsYLoop:
    exx     ; // use bc', de', hl'

    ld  a, (bc) ; // load sin_pts_y
    add a, (hl) ; // add sin_adds_y
    ld  (bc), a ; // store acc into sin_pts_y value
    ld  (de), a ; // store acc into sin_pts_x value

    inc bc
    inc de
    inc hl

    exx     ; // use bc, de, hl

    dec d
    jp  NZ, SinPtsYLoop
    ; // END SinPtsYLoop

    ld b, #SCREEN_COLUMNS

XLoop:
    exx     ; // use bc', de', hl'

    ld  de, #_sin_pts_x
    ld  hl, #_sin_adds_x
    ld  b, #PLASMA_PTS

SinPtsXLoop:
    ld  a, (de) ; // sin_pts_x
    add a, (hl) ; // sin_adds_x
    ld  (de), a

    inc de
    inc hl
    djnz SinPtsXLoop
    ; // END SinPtsXLoop

    ld  de, #_sin_pts_x ; // reset the pointer to sin_pts_x
    xor a               ; // clear the accumulator
    ld  b, #PLASMA_PTS

SinAddLoop:
    ex  af, af' ;' // use af'
    ld  a, (de)

    ld  hl, #_sintab    ; // not as nice as the page-aligned version, ah well

    ; // add hl, a -- from https://plutiedev.com/z80-add-8bit-to-16bit et al
    add   a, l    ; // a = a + l
    ld    l, a    ; // l = a + l
    adc   a, h    ; // a = a + l + h + (carry)
    sub   l       ; // a = h + (carry)
    ld    h, a    ; // h = h + (carry)

    ex  af, af' ;' // use af

    add a, (hl) ; // Add sine value from the table
    inc de
    djnz SinAddLoop
    ; // END SinAddLoop

    exx ; // use bc, de, hl
    ld  (hl), a ; // save compiled sine number back into plasma_starts
    inc hl
    djnz XLoop
    ; // END XLoop

    dec c
    jp  NZ, YLoop
    ; // END YLoop

    ret
__endasm;
    // clang-format on
    /*
        // C implementation (good readability, but unoptimal when compiled)

        // Calc plasma starting Y values
        for (i = 0; i < PLASMA_PTS; i++)
            sin_pts_y[i] = sin_starts_y[i];

        // Y loop
        for (i = 0; i < SCREEN_ROWS; i++)
        {
            // Sine points Y loop
            for (j = 0; j < PLASMA_PTS; j++)
            {
                sin_pts_y[j] = sin_pts_y[j] + sin_adds_y[j];
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

                arr_offset = (i * SCREEN_COLUMNS) + j;
                plasma_base[arr_offset] = plasma_value;
            }
        }
    */
}

// Animate
// D(n,y) = (sin(S1 * n + P1 * y) + sin(S2 * n + P2 * y)) / 2 + C * n
// Where y(Row), n(Frame), S(sin_speeds), P(plasma_freqs), C(cycle_speed)
void animate_buffer(void)
{
    uint8_t row_count, col_count,
        sin_1, sin_2,
        distortion_val,
        *plasma_arr = plasma_starts,
        *buffer_arr = screen_buffer,
        *buffer_end = screen_buffer + SCREEN_SIZE;
    const uint8_t cur_speed = cycle_speed * frame_count,
                  plasma_speed_1 = sin_speeds_1 * frame_count,
                  plasma_speed_2 = sin_speeds_2 * frame_count;

    row_count = 0;

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
