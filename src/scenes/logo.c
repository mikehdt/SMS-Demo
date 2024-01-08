#include "logo.h"
#include "../assets2banks.h"
#include "../engine/global_constants.h"
#include "../engine/scenes.h"
#include "../engine/tilemap.h"
#include "../libs/SMSlib.h"

uint8_t curXCycle, paletteIn[10];

#define X_OFFSET 11
#define Y_OFFSET 10
#define LOGO_TILES 10
#define TRAIL 8
#define PALETTE_CYCLE 2

void logo_init(void)
{
    cur_stage = 1;
    cur_frame = 0;
    curXCycle = 0;

    paletteIn[0] = 0x00;
    paletteIn[1] = 0x00;
    paletteIn[2] = 0x10;
    paletteIn[3] = 0x11;
    paletteIn[4] = 0x12;
    paletteIn[5] = 0x17;
    paletteIn[6] = 0x1b;
    paletteIn[7] = 0x1f;
    paletteIn[8] = 0x3f;
    paletteIn[9] = 0x3f;

    SMS_displayOff();
    SMS_waitForVBlank();

    clear_tilemap(0);

    SMS_loadBGPalette(paletteIn);
    SMS_mapROMBank(da_mini_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(da_mini_tiles_psgcompr, 1);
    SMS_displayOn();
}

void logo_update(void)
{
    // --- STAGES ---
    SMS_waitForVBlank();
    SMS_waitForVBlank();

    // Palette cycling
    if (cur_stage == 1)
        for (int i = 0; i <= 16 - PALETTE_CYCLE; i++)
            SMS_setBGPaletteColor(i + 1, paletteIn[i + curXCycle]);
    else if (cur_stage == 3)
        for (int i = 0; i <= 16 - PALETTE_CYCLE; i++)
            SMS_setBGPaletteColor(i + 1, paletteIn[i + PALETTE_CYCLE - curXCycle - 1]);

    // 1. Fade In
    if (cur_stage == 1 && curXCycle == 0)
    {
        int8_t startPos = cur_frame - TRAIL + 1;

        // Limiter
        if (startPos < 0)
            startPos = 0;

        for (int i = startPos; i <= cur_frame; i++)
        {
            // This may be more efficient as a pointer to the tilemap?
            // SMS_debugPrintf("i: %d\n", i);
            if (i >= LOGO_TILES)
                break;

            int8_t mult = LOGO_TILES * (cur_frame - i);

            if (mult < 0)
                mult = 0;

            SMS_setTileatXY(X_OFFSET + i, Y_OFFSET, i + mult + 1);
        }

        // Stage kick
        if (++cur_frame > LOGO_TILES + TRAIL)
        {
            cur_stage = 2;
            cur_frame = 0;
        }
    }

    // 2. Pause
    if (cur_stage == 2)
    {
        if (++cur_frame > 24)
        {
            cur_stage = 3;
            cur_frame = 0;
        }
    }

    // 3. Fade Out
    if (cur_stage == 3 && curXCycle == 0)
    {
        int8_t startPos = cur_frame - TRAIL + 1;

        // Limiter
        if (startPos < 0)
            startPos = 0;

        for (int i = startPos; i <= cur_frame; i++)
        {
            // This may be more efficient as a pointer to the tilemap?
            // SMS_debugPrintf("i: %d\n", i);
            if (i >= LOGO_TILES)
                break;

            int8_t mult = cur_frame - i;

            if (mult < 0)
                mult = 0;

            mult = TRAIL - mult - 2;

            if (mult == -1)
            {
                // Blank tile; erase
                SMS_setTileatXY(X_OFFSET + i, Y_OFFSET, 0);
                continue;
            }

            // Add TRAIL for the palette inversion
            SMS_setTileatXY(X_OFFSET + i, Y_OFFSET, i + (LOGO_TILES * (mult + TRAIL)) + 1);
        }

        // Stage kick
        if (++cur_frame > LOGO_TILES + TRAIL)
        {
            SMS_VRAMmemsetW(XYtoADDR(11, 10), 0, (LOGO_TILES * 2));
            cur_stage = 4;
            cur_frame = 0;
        }
    }

    if (cur_stage == 4)
    {
        SMS_loadBGPalette(credits_palette_bin);

        if (cur_frame == 10)
        {
            SMS_loadPSGaidencompressedTiles(credit_title_code_tiles_psgcompr, 189);

            for (int i = 189; i <= 194; i++)
                SMS_setTileatXY(13 + (i - 189), 7, i);
            for (int i = 195; i <= 200; i++)
                SMS_setTileatXY(13 + (i - 195), 8, i);
        }

        if (cur_frame == 20)
        {
            SMS_loadPSGaidencompressedTiles(credit_bananaboy_tiles_psgcompr, 151);

            SMS_setTileatXY(12, 9, 151);
            SMS_setTileatXY(17, 9, 153);
            for (int i = 154; i <= 161; i++)
                SMS_setTileatXY(12 + (i - 154), 10, i);
            SMS_setTileatXY(19, 11, 162);
        }

        if (cur_frame == 30)
        {
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
            cur_stage = 5;
            cur_frame = 0;
        }
    }

    if (cur_stage == 5)
    {
        if (cur_frame == 20)
        {
            SMS_loadPSGaidencompressedTiles(credit_title_graphics_tiles_psgcompr, 201);

            for (int i = 201; i <= 210; i++)
                SMS_setTileatXY(11 + (i - 201), 7, i);
            for (int i = 211; i <= 220; i++)
                SMS_setTileatXY(11 + (i - 211), 8, i);
        }

        if (cur_frame == 30)
        {
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
            cur_stage = 6;
            cur_frame = 0;
        }
    }

    if (cur_stage == 6)
    {
        if (cur_frame == 20)
        {
            SMS_loadPSGaidencompressedTiles(credit_title_music_tiles_psgcompr, 221);

            for (int i = 221; i <= 228; i++)
                SMS_setTileatXY(12 + (i - 221), 7, i);
            for (int i = 229; i <= 236; i++)
                SMS_setTileatXY(12 + (i - 229), 8, i);
        }

        if (cur_frame == 30)
        {
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

    // Pause cycle for palette cycling
    if ((cur_stage == 1 || cur_stage == 3) && ++curXCycle == PALETTE_CYCLE)
        curXCycle = 0;
}

void logo_end(void)
{
    // SMS_waitForVBlank();
}
