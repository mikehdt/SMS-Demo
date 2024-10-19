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

uint8_t col_limit = 0, sprite_count = 0, sprite_offset = 8, eye_count = 0, fade_sine = 0;

void sineline_init(void)
{
    cur_stage = 1;
    sineline_ptr = 0;

    SMS_waitForVBlank();
    SMS_mapROMBank(small_sine_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(small_sine_tiles_psgcompr, 0);
    SMS_loadBGPalette(small_sine_palette_bin);

    clear_tilemap(0);

    // Note to self: use first half sprites toggling probably needs to be smarter
    SMS_initSprites();
    SMS_setSpriteMode(SPRITEMODE_ZOOMED);

    SMS_mapROMBank(spheres_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(spheres_tiles_psgcompr, 256);
    SMS_loadSpritePalette(spheres_palette_bin);

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
                SMS_setTileatXY(4, 12, 261 | TILE_USE_SPRITE_PALETTE);
                SMS_setTileatXY(11, 1, 262 | TILE_USE_SPRITE_PALETTE);
                break;
            }
            case 1:
            {
                SMS_setTileatXY(7, 5, 262 | TILE_USE_SPRITE_PALETTE);
                SMS_setTileatXY(22, 16, 263 | TILE_USE_SPRITE_PALETTE);
                break;
            }
            case 2:
            {
                SMS_setTileatXY(19, 3, 260 | TILE_USE_SPRITE_PALETTE);
                SMS_setTileatXY(9, 14, 262 | TILE_USE_SPRITE_PALETTE);
                break;
            }
            case 3:
            {
                SMS_setTileatXY(13, 19, 261 | TILE_USE_SPRITE_PALETTE);
                break;
            }
            case 4:
            {
                SMS_setTileatXY(24, 22, 261 | TILE_USE_SPRITE_PALETTE);
                SMS_setTileatXY(6, 23, 261 | TILE_USE_SPRITE_PALETTE);
                break;
            }
            case 5:
            {
                SMS_setTileatXY(31, 18, 262 | TILE_USE_SPRITE_PALETTE);
                break;
            }
            case 6:
            {
                SMS_setTileatXY(1, 2, 263 | TILE_USE_SPRITE_PALETTE);
                SMS_setTileatXY(22, 0, 261 | TILE_USE_SPRITE_PALETTE);
                break;
            }
            case 7:
            {
                SMS_setTileatXY(18, 15, 262 | TILE_USE_SPRITE_PALETTE);
                SMS_setTileatXY(29, 4, 260 | TILE_USE_SPRITE_PALETTE);
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
        for (i = 0; i < eye_count; i++)
        {
            // SMS_updateSpritePosition(i, 8 + (i * 32), 72);
            SMS_updateSpriteImage(i, 257 + cur_frame % 4);
        }

        SMS_copySpritestoSAT();
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
