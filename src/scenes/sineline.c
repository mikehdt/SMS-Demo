#include "sineline.h"
#include "../assets2banks.h"
#include "../engine/global_constants.h"
#include "../engine/palettes.h"
#include "../engine/scenes.h"
#include "../engine/sprites.h"
#include "../engine/tilemap.h"
#include "../libs/SMSlib.h"
#include <stdint.h>

uint16_t sineline_ptr,
    sineline[104] = {
        1, 19, 37, 15 | TILE_FLIPPED_Y,  // 0
        2, 20, 38, 0,                    // 1
        3, 21, 39, 0,                    // 2
        4, 22, 0, 0,                     // 3
        5, 23, 0, 0,                     // 4
        6, 15 | TILE_FLIPPED_Y, 0, 0,    // 5
        7, 0, 0, 0,                      // 6
        8, 0, 0, 0,                      // 7
        9, 16 | TILE_FLIPPED_Y, 0, 0,    // 8
        10, 24, 0, 0,                    // 9
        11, 25, 0, 0,                    // 10
        12, 26, 40, 0,                   // 11
        13, 27, 41, 0,                   // 12
        14, 28, 42, 16 | TILE_FLIPPED_Y, // 13
        0, 29, 43, 55,                   // 14
        0, 30, 44, 56,                   // 15
        0, 15, 31, 45,                   // 16
        0, 0, 32, 46,                    // 17
        0, 0, 14, 47,                    // 18
        0, 0, 0, 48,                     // 19
        0, 0, 0, 49,                     // 20
        0, 0, 1, 50,                     // 21
        0, 0, 33, 51,                    // 22
        0, 16, 34, 52,                   // 23
        0, 17, 35, 53,                   // 24
        0, 18, 36, 54,                   // 25
};

uint8_t col_limit = 0, sprite_count = 0, sprite_offset = 8, eye_count = 0, fade_sine;

struct bg_eye
{
    int x, y, tile;
};

struct bg_eye bg_eyes[14];

void sineline_init(void)
{
    cur_stage = 1;
    fade_sine = 0;
    sineline_ptr = 0;

    bg_eyes[0].x = 4;
    bg_eyes[0].y = 12;
    bg_eyes[0].tile = 261;
    bg_eyes[1].x = 11;
    bg_eyes[1].y = 1;
    bg_eyes[1].tile = 262;
    bg_eyes[2].x = 7;
    bg_eyes[2].y = 5;
    bg_eyes[2].tile = 265;
    bg_eyes[3].x = 22;
    bg_eyes[3].y = 16;
    bg_eyes[3].tile = 263;
    bg_eyes[4].x = 19;
    bg_eyes[4].y = 3;
    bg_eyes[4].tile = 260;
    bg_eyes[5].x = 9;
    bg_eyes[5].y = 14;
    bg_eyes[5].tile = 262;
    bg_eyes[6].x = 13;
    bg_eyes[6].y = 19;
    bg_eyes[6].tile = 267;
    bg_eyes[7].x = 24;
    bg_eyes[7].y = 22;
    bg_eyes[7].tile = 261;
    bg_eyes[8].x = 6;
    bg_eyes[8].y = 23;
    bg_eyes[8].tile = 264;
    bg_eyes[9].x = 31;
    bg_eyes[9].y = 18;
    bg_eyes[9].tile = 262;
    bg_eyes[10].x = 1;
    bg_eyes[10].y = 2;
    bg_eyes[10].tile = 263;
    bg_eyes[11].x = 22;
    bg_eyes[11].y = 0;
    bg_eyes[11].tile = 261;
    bg_eyes[12].x = 18;
    bg_eyes[12].y = 15;
    bg_eyes[12].tile = 265;
    bg_eyes[13].x = 29;
    bg_eyes[13].y = 4;
    bg_eyes[13].tile = 264;

    SMS_waitForVBlank();
    // Note to self: use first half sprites toggling probably needs to be smarter
    SMS_initSprites();
    SMS_setSpriteMode(SPRITEMODE_ZOOMED);

    SMS_mapROMBank(spheres_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(spheres_tiles_psgcompr, 256);
    SMS_loadSpritePalette(spheres_palette_bin);

    SMS_mapROMBank(small_sine_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(small_sine_tiles_psgcompr, 0);
    SMS_loadBGPalette(small_sine_palette_bin);

    clear_tilemap(0);

    SMS_waitForVBlank();
}

void sineline_update(void)
{
    uint8_t i;
    uint16_t cur_tile;

    // le pause
    SMS_waitForVBlank();
    SMS_waitForVBlank();

    if (cur_stage == 1 && cur_frame % 4 == 0)
    {
        // SMS_debugPrintf("eye_count: %d\n", eye_count);
        SMS_addSprite(8 + (eye_count * 32), 72, 260);
        SMS_copySpritestoSAT();

        switch (eye_count)
        {
            case 0:
            {
                SMS_setTileatXY(bg_eyes[0].x, bg_eyes[0].y, bg_eyes[0].tile | TILE_USE_SPRITE_PALETTE);
                SMS_setTileatXY(bg_eyes[1].x, bg_eyes[1].y, bg_eyes[1].tile | TILE_USE_SPRITE_PALETTE);
                break;
            }
            case 1:
            {
                SMS_setTileatXY(bg_eyes[2].x, bg_eyes[2].y, bg_eyes[2].tile | TILE_USE_SPRITE_PALETTE);
                SMS_setTileatXY(bg_eyes[3].x, bg_eyes[3].y, bg_eyes[3].tile | TILE_USE_SPRITE_PALETTE);
                break;
            }
            case 2:
            {
                SMS_setTileatXY(bg_eyes[4].x, bg_eyes[4].y, bg_eyes[4].tile | TILE_USE_SPRITE_PALETTE);
                SMS_setTileatXY(bg_eyes[5].x, bg_eyes[5].y, bg_eyes[5].tile | TILE_USE_SPRITE_PALETTE);
                break;
            }
            case 3:
            {
                SMS_setTileatXY(bg_eyes[6].x, bg_eyes[6].y, bg_eyes[6].tile | TILE_USE_SPRITE_PALETTE);
                break;
            }
            case 4:
            {
                SMS_setTileatXY(bg_eyes[7].x, bg_eyes[7].y, bg_eyes[7].tile | TILE_USE_SPRITE_PALETTE);
                SMS_setTileatXY(bg_eyes[8].x, bg_eyes[8].y, bg_eyes[8].tile | TILE_USE_SPRITE_PALETTE);
                break;
            }
            case 5:
            {
                SMS_setTileatXY(bg_eyes[9].x, bg_eyes[9].y, bg_eyes[9].tile | TILE_USE_SPRITE_PALETTE);
                break;
            }
            case 6:
            {
                SMS_setTileatXY(bg_eyes[10].x, bg_eyes[10].y, bg_eyes[10].tile | TILE_USE_SPRITE_PALETTE);
                SMS_setTileatXY(bg_eyes[11].x, bg_eyes[11].y, bg_eyes[11].tile | TILE_USE_SPRITE_PALETTE);
                break;
            }
            case 7:
            {
                SMS_setTileatXY(bg_eyes[12].x, bg_eyes[12].y, bg_eyes[12].tile | TILE_USE_SPRITE_PALETTE);
                SMS_setTileatXY(bg_eyes[13].x, bg_eyes[13].y, bg_eyes[13].tile | TILE_USE_SPRITE_PALETTE);
                break;
            }
        }

        if (eye_count++ > 8)
        {
            eye_count = 8;
            cur_stage = 2;
        }
    }

    for (i = 0; i < col_limit; i++)
    {
        cur_tile = ((i + sineline_ptr) << 2) % 104; // 104 = length of the array
        // SMS_debugPrintf("cur_tile: %d\n", cur_tile);

        uint16_t priority = (cur_tile > (8 << 2) && cur_tile < (18 << 2)) ? TILE_PRIORITY : 0;

        SMS_setTileatXY(i, 8, sineline[cur_tile] | priority);
        SMS_setTileatXY(i, 9, sineline[cur_tile + 1] | priority);
        SMS_setTileatXY(i, 10, sineline[cur_tile + 2] | priority);
        SMS_setTileatXY(i, 11, sineline[cur_tile + 3] | priority);
    }

    if (col_limit != SCREEN_COLUMNS && sineline_ptr % 2 == 0)
    {
        if (++col_limit > SCREEN_COLUMNS)
            col_limit = SCREEN_COLUMNS;
    }

    if (++sineline_ptr > 25)
        sineline_ptr = 0;

    if (cur_frame % 5 == 0)
    {
        uint8_t sprite_tile;

        for (i = 0; i < eye_count; i++)
        {
            sprite_tile = cur_frame % 4 + i;

            if (sprite_tile > 4)
                sprite_tile = sprite_tile % 4;

            SMS_updateSpriteImage(i, 256 + sprite_tile);
        }

        SMS_copySpritestoSAT();
    }

    if (cur_stage == 2 && cur_frame % 2 == 0)
    {
        for (i = 0; i < 14; i++)
        {
            if (++bg_eyes[i].tile > 271)
                bg_eyes[i].tile = 260;

            SMS_setTileatXY(bg_eyes[i].x, bg_eyes[i].y, bg_eyes[i].tile | TILE_USE_SPRITE_PALETTE);
        }
    }

    if (cur_frame++ > 130)
    {
        fade_to_black(small_sine_palette_bin, fade_sine);

        if (fade_sine++ > 9)
        {
            fade_sine = 0;
            next_scene();
        }
    }
}

void sineline_end(void)
{
    SMS_waitForVBlank();
    SMS_setSpriteMode(SPRITEMODE_NORMAL);
    clear_sprites();
}
