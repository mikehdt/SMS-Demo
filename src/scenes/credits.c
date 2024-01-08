#include "credits.h"
#include "../assets2banks.h"
#include "../engine/scenes.h"
#include "../engine/tilemap.h"
#include "../libs/SMSlib.h"

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

            for (int i = 1; i <= 6; i++)
                SMS_setTileatXY(13 + (i - 1), 7, i);
            for (int i = 7; i <= 12; i++)
                SMS_setTileatXY(13 + (i - 7), 8, i);
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
            SMS_loadPSGaidencompressedTiles(credit_title_graphics_tiles_psgcompr, 201);

            for (int i = 201; i <= 210; i++)
                SMS_setTileatXY(11 + (i - 201), 7, i);
            for (int i = 211; i <= 220; i++)
                SMS_setTileatXY(11 + (i - 211), 8, i);
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
            SMS_loadPSGaidencompressedTiles(credit_title_music_tiles_psgcompr, 221);

            for (int i = 221; i <= 228; i++)
                SMS_setTileatXY(12 + (i - 221), 7, i);
            for (int i = 229; i <= 236; i++)
                SMS_setTileatXY(12 + (i - 229), 8, i);
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
            next_scene();
        }
    }
}
