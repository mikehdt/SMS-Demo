#include "credits.h"
#include "../assets2banks.h"
#include "../engine/scenes.h"
#include "../engine/tilemap.h"
#include "../libs/SMSlib.h"

#define TITLE_CODE 1
#define TITLE_GRAPHICS 13
#define TITLE_MUSIC 33
// TBC
#define TITLE_BANANABOY 1
#define TITLE_DARKOWL 1
#define TITLE_SHOCK 1
#define TITLE_CTRIX 1

void credits_init(void)
{
    cur_stage = 1;
    cur_frame = 0;

    SMS_mapROMBank(credits_palette_bin_bank);
    SMS_loadBGPalette(credits_palette_bin);
}

void credits_update(void)
{
    SMS_waitForVBlank();
    SMS_waitForVBlank();

    if (cur_stage == 1)
    {
        if (cur_frame == 10)
        {
            // CODE
            SMS_loadPSGaidencompressedTiles(credit_title_code_tiles_psgcompr, 1);

            for (int i = TITLE_CODE; i < TITLE_CODE + 6; i++)
                SMS_setTileatXY(13 + (i - TITLE_CODE), 7, i);
            for (int i = TITLE_CODE + 6; i < TITLE_CODE + 12; i++)
                SMS_setTileatXY(13 + (i - TITLE_CODE - 6), 8, i);
        }

        if (cur_frame == 20)
        {
            // Bananaboy
            SMS_loadPSGaidencompressedTiles(credit_bananaboy_tiles_psgcompr, 151);

            SMS_setTileatXY(12, 9, 151);
            SMS_setTileatXY(17, 9, 153);
            for (int i = 154; i <= 161; i++)
                SMS_setTileatXY(12 + (i - 154), 10, i);
            SMS_setTileatXY(19, 11, 162);
        }

        if (cur_frame == 30)
        {
            // darkowl
            SMS_loadPSGaidencompressedTiles(credit_darkowl_tiles_psgcompr, 163);

            SMS_setTileatXY(13, 11, 163);
            SMS_setTileatXY(14, 11, 164);
            SMS_setTileatXY(15, 11, 165);
            SMS_setTileatXY(18, 11, 167);
            for (int i = 168; i <= 173; i++)
                SMS_setTileatXY(13 + (i - 168), 12, i);
        }

        if (cur_frame == 40)
        {
            // sh0ck
            SMS_loadPSGaidencompressedTiles(credit_sh0ck_tiles_psgcompr, 174);

            SMS_setTileatXY(14, 13, 174);
            SMS_setTileatXY(15, 13, 175);
            SMS_setTileatXY(16, 13, 175 | TILE_FLIPPED_X);
            SMS_setTileatXY(17, 13, 176);
            for (int i = 177; i <= 180; i++)
                SMS_setTileatXY(14 + (i - 177), 14, i);
        }

        if (++cur_frame > 70)
        {
            clear_tilemap(0);
            cur_stage = 2;
            cur_frame = 0;
        }
    }
    else if (cur_stage == 2)
    {
        if (cur_frame == 20)
        {
            // GRAPHICS
            SMS_loadPSGaidencompressedTiles(credit_title_graphics_tiles_psgcompr, TITLE_GRAPHICS);

            for (int i = TITLE_GRAPHICS; i < TITLE_GRAPHICS + 10; i++)
                SMS_setTileatXY(11 + (i - TITLE_GRAPHICS), 7, i);
            for (int i = TITLE_GRAPHICS + 10; i < TITLE_GRAPHICS + 20; i++)
                SMS_setTileatXY(11 + (i - TITLE_GRAPHICS - 10), 8, i);
        }

        if (cur_frame == 30)
        {
            // darkowl
            SMS_setTileatXY(13, 9, 163);
            SMS_setTileatXY(14, 9, 164);
            SMS_setTileatXY(15, 9, 165);
            SMS_setTileatXY(18, 9, 167);
            for (int i = 168; i <= 173; i++)
                SMS_setTileatXY(13 + (i - 168), 10, i);
        }

        if (++cur_frame > 60)
        {
            clear_tilemap(0);
            cur_stage = 3;
            cur_frame = 0;
        }
    }
    else if (cur_stage == 3)
    {
        if (cur_frame == 20)
        {
            // MUSIC
            SMS_loadPSGaidencompressedTiles(credit_title_music_tiles_psgcompr, TITLE_MUSIC);

            for (int i = TITLE_MUSIC; i < TITLE_MUSIC + 8; i++)
                SMS_setTileatXY(12 + (i - TITLE_MUSIC), 7, i);
            for (int i = TITLE_MUSIC + 8; i < TITLE_MUSIC + 16; i++)
                SMS_setTileatXY(12 + (i - TITLE_MUSIC - 8), 8, i);
        }

        if (cur_frame == 30)
        {
            // cTrix
            SMS_loadPSGaidencompressedTiles(credit_ctrix_tiles_psgcompr, 181);

            SMS_setTileatXY(14, 9, 181);
            SMS_setTileatXY(15, 9, 182);
            SMS_setTileatXY(16, 9, 183);
            for (int i = 185; i <= 188; i++)
                SMS_setTileatXY(14 + (i - 185), 10, i);
        }

        if (++cur_frame > 60)
        {
            clear_tilemap(0);
            // cur_frame = 0;
            // cur_stage = 1;
            next_scene();
        }
    }
}
