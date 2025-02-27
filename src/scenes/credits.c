#include "credits.h"
#include "../assets2banks.h"
#include "../engine/scenes.h"
#include "../engine/tilemap.h"
#include "../libs/SMSlib.h"

#define TITLE_CODE 1 + 256
#define TITLE_GRAPHICS 13 + 256
#define TITLE_MUSIC 33 + 256
// TBC
#define TITLE_BANANABOY 49 + 256
#define TITLE_DARKOWL 61 + 256
#define TITLE_SHOCK 72 + 256
#define TITLE_CTRIX 79 + 256

void credits_init(void)
{
    if (cur_stage == 1)
    {
        SMS_mapROMBank(blank_tiles_psgcompr_bank);
        SMS_loadPSGaidencompressedTiles(blank_tiles_psgcompr, 256);
        SMS_mapROMBank(credits_palette_bin_bank);
        SMS_loadSpritePalette(credits_palette_bin);
    }
    else
    {
        SMS_mapROMBank(credits_palette_bin_bank);
    }

    clear_tilemap(256 | TILE_USE_SPRITE_PALETTE);
}

void credits_update(void)
{
    SMS_waitForVBlank();
    SMS_waitForVBlank();

    if (cur_stage == 1)
    {
        if (cur_frame == 15)
        {
            // CODE
            SMS_loadPSGaidencompressedTiles(credit_title_code_tiles_psgcompr, TITLE_CODE);

            for (int i = TITLE_CODE; i < TITLE_CODE + 6; i++)
                SMS_setTileatXY(13 + (i - TITLE_CODE), 7, i | TILE_USE_SPRITE_PALETTE);
            for (int i = TITLE_CODE + 6; i < TITLE_CODE + 12; i++)
                SMS_setTileatXY(13 + (i - TITLE_CODE - 6), 8, i | TILE_USE_SPRITE_PALETTE);
        }
        else if (cur_frame == 30)
        {
            // Bananaboy
            SMS_loadPSGaidencompressedTiles(credit_bananaboy_tiles_psgcompr, TITLE_BANANABOY);

            SMS_setTileatXY(12, 9, TITLE_BANANABOY | TILE_USE_SPRITE_PALETTE);
            SMS_setTileatXY(17, 9, (TITLE_BANANABOY + 2) | TILE_USE_SPRITE_PALETTE);
            for (int i = TITLE_BANANABOY + 3; i <= TITLE_BANANABOY + 10; i++)
                SMS_setTileatXY(12 + (i - TITLE_BANANABOY - 3), 10, i | TILE_USE_SPRITE_PALETTE);
            SMS_setTileatXY(19, 11, (TITLE_BANANABOY + 11) | TILE_USE_SPRITE_PALETTE);
        }
        else if (cur_frame == 45)
        {
            // darkowl
            SMS_loadPSGaidencompressedTiles(credit_darkowl_tiles_psgcompr, TITLE_DARKOWL);

            SMS_setTileatXY(13, 11, TITLE_DARKOWL | TILE_USE_SPRITE_PALETTE);
            SMS_setTileatXY(14, 11, (TITLE_DARKOWL + 1) | TILE_USE_SPRITE_PALETTE);
            SMS_setTileatXY(15, 11, (TITLE_DARKOWL + 2) | TILE_USE_SPRITE_PALETTE);
            SMS_setTileatXY(18, 11, (TITLE_DARKOWL + 4) | TILE_USE_SPRITE_PALETTE);
            for (int i = TITLE_DARKOWL + 5; i <= TITLE_DARKOWL + 10; i++)
                SMS_setTileatXY(13 + (i - TITLE_DARKOWL - 5), 12, i | TILE_USE_SPRITE_PALETTE);
        }
        else if (cur_frame == 60)
        {
            // sh0ck
            SMS_loadPSGaidencompressedTiles(credit_sh0ck_tiles_psgcompr, TITLE_SHOCK);

            SMS_setTileatXY(14, 13, TITLE_SHOCK | TILE_USE_SPRITE_PALETTE);
            SMS_setTileatXY(15, 13, (TITLE_SHOCK + 1) | TILE_USE_SPRITE_PALETTE);
            SMS_setTileatXY(16, 13, (TITLE_SHOCK + 1) | TILE_FLIPPED_X | TILE_USE_SPRITE_PALETTE);
            SMS_setTileatXY(17, 13, (TITLE_SHOCK + 2) | TILE_USE_SPRITE_PALETTE);
            for (int i = TITLE_SHOCK + 3; i <= TITLE_SHOCK + 6; i++)
                SMS_setTileatXY(14 + (i - TITLE_SHOCK - 3), 14, i | TILE_USE_SPRITE_PALETTE);
        }

        if (++cur_frame == 90)
        {
            next_scene();
        }
    }
    else if (cur_stage == 2)
    {
        if (cur_frame == 15)
        {
            // GRAPHICS
            SMS_loadPSGaidencompressedTiles(credit_title_graphics_tiles_psgcompr, TITLE_GRAPHICS);

            for (int i = TITLE_GRAPHICS; i < TITLE_GRAPHICS + 10; i++)
                SMS_setTileatXY(11 + (i - TITLE_GRAPHICS), 7, i | TILE_USE_SPRITE_PALETTE);
            for (int i = TITLE_GRAPHICS + 10; i < TITLE_GRAPHICS + 20; i++)
                SMS_setTileatXY(11 + (i - TITLE_GRAPHICS - 10), 8, i | TILE_USE_SPRITE_PALETTE);
        }
        else if (cur_frame == 30)
        {
            // darkowl
            SMS_loadPSGaidencompressedTiles(credit_darkowl_tiles_psgcompr, TITLE_DARKOWL);

            SMS_setTileatXY(13, 9, TITLE_DARKOWL | TILE_USE_SPRITE_PALETTE);
            SMS_setTileatXY(14, 9, (TITLE_DARKOWL + 1) | TILE_USE_SPRITE_PALETTE);
            SMS_setTileatXY(15, 9, (TITLE_DARKOWL + 2) | TILE_USE_SPRITE_PALETTE);
            SMS_setTileatXY(18, 9, (TITLE_DARKOWL + 4) | TILE_USE_SPRITE_PALETTE);
            for (int i = TITLE_DARKOWL + 5; i <= TITLE_DARKOWL + 10; i++)
                SMS_setTileatXY(13 + (i - TITLE_DARKOWL - 5), 10, i | TILE_USE_SPRITE_PALETTE);
        }
        else if (cur_frame == 60)
        {
            clear_tilemap(256 | TILE_USE_SPRITE_PALETTE);
        }

        if (++cur_frame == 90)
        {
            next_scene();
        }
    }
    else if (cur_stage == 3)
    {
        if (cur_frame == 15)
        {
            // MUSIC
            SMS_loadPSGaidencompressedTiles(credit_title_music_tiles_psgcompr, TITLE_MUSIC);

            for (int i = TITLE_MUSIC; i < TITLE_MUSIC + 8; i++)
                SMS_setTileatXY(12 + (i - TITLE_MUSIC), 7, i | TILE_USE_SPRITE_PALETTE);
            for (int i = TITLE_MUSIC + 8; i < TITLE_MUSIC + 16; i++)
                SMS_setTileatXY(12 + (i - TITLE_MUSIC - 8), 8, i | TILE_USE_SPRITE_PALETTE);
        }
        else if (cur_frame == 30)
        {
            // cTrix
            SMS_loadPSGaidencompressedTiles(credit_ctrix_tiles_psgcompr, TITLE_CTRIX);

            SMS_setTileatXY(14, 9, TITLE_CTRIX | TILE_USE_SPRITE_PALETTE);
            SMS_setTileatXY(15, 9, (TITLE_CTRIX + 1) | TILE_USE_SPRITE_PALETTE);
            SMS_setTileatXY(16, 9, (TITLE_CTRIX + 2) | TILE_USE_SPRITE_PALETTE);
            for (int i = TITLE_CTRIX + 4; i <= TITLE_CTRIX + 7; i++)
                SMS_setTileatXY(14 + (i - TITLE_CTRIX - 4), 10, i | TILE_USE_SPRITE_PALETTE);
        }
        else if (cur_frame == 60)
        {
            clear_tilemap(256 | TILE_USE_SPRITE_PALETTE);
        }

        if (++cur_frame == 90)
        {
            next_scene();
        }
    }
}

void credits_end(void)
{
    SMS_mapROMBank(credits_palette_bin_bank);
    SMS_loadBGPalette(credits_palette_bin);

    clear_tilemap(0);
}
