#include "../assets2banks.h"
#include "../engine/scenes.h"
#include "../engine/tilemap.h"
#include "../libs/SMSlib.h"
#include "logo.h"

uint8_t curXCycle, paletteIn[10];

#define X_OFFSET 11
#define Y_OFFSET 10
#define LOGO_TILES 10
#define TRAIL 8
#define PALETTE_CYCLE 2

void logo_init(void)
{
    cur_stage = 1;
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
            cur_stage = 1;
            next_scene();
        }
    }

    // Pause cycle for palette cycling
    if ((cur_stage == 1 || cur_stage == 3) && ++curXCycle == PALETTE_CYCLE)
        curXCycle = 0;
}
