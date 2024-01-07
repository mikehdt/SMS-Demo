#include "logo.h"
#include "../assets2banks.h"
#include "../engine/global_constants.h"
#include "../engine/scenes.h"
#include "../engine/tilemap.h"
#include "../libs/SMSlib.h"

int8_t curXPos;
uint8_t curXCycle, paletteIn[16];

#define X_OFFSET 11
#define Y_OFFSET 10
#define LOGO_TILES 10
#define TRAIL 9
#define PALETTE_CYCLE 2

void logo_init(void)
{
    cur_stage = 1;
    curXPos = 0;
    curXCycle = 0;

    paletteIn[0] = 0x00;
    paletteIn[1] = 0x00;
    paletteIn[2] = 0x10;
    paletteIn[3] = 0x11;
    paletteIn[4] = 0x12;
    paletteIn[5] = 0x13;
    paletteIn[6] = 0x17;
    paletteIn[7] = 0x1b;
    paletteIn[8] = 0x1f;
    paletteIn[9] = 0x3f;
    paletteIn[10] = 0x3f;
    paletteIn[11] = 0x3f;
    paletteIn[12] = 0x3f;
    paletteIn[13] = 0x3f;
    paletteIn[14] = 0x3f;
    paletteIn[15] = 0x3f;

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
    SMS_waitForVBlank();
    SMS_waitForVBlank();

    if (cur_stage == 1)
    {
        for (int i = 0; i <= 16 - PALETTE_CYCLE; i++)
        {
            SMS_setBGPaletteColor(i + 1, paletteIn[i + curXCycle]);
            SMS_debugPrintf("iter %d, color %d\n", i, paletteIn[i + PALETTE_CYCLE - curXCycle - 1]);
        }
    }
    else if (cur_stage == 3)
    {
        for (int i = 0; i <= 16 - PALETTE_CYCLE; i++)
        {
            SMS_setBGPaletteColor(i + 1, paletteIn[i + PALETTE_CYCLE - curXCycle - 1]);
        }
    }

    if (cur_stage == 1 && curXCycle == 0)
    {
        int8_t startPos = curXPos - TRAIL + 1;

        // Limiter
        if (startPos < 0)
            startPos = 0;

        for (int i = startPos; i <= curXPos; i++)
        {
            // This may be more efficient as a pointer to the tilemap?
            // SMS_debugPrintf("i: %d\n", i);
            if (i >= LOGO_TILES)
                break;

            int8_t mult = LOGO_TILES * (curXPos - i);

            if (mult < 0)
                mult = 0;

            SMS_setTileatXY(X_OFFSET + i, Y_OFFSET, i + mult + 1);
        }

        // Stage kick
        if (++curXPos > LOGO_TILES + TRAIL)
        {
            cur_stage = 2;
            curXPos = 0;
        }
    }

    // Pause between fade in and out
    if (cur_stage == 2)
    {
        if (++curXPos > 24)
        {
            cur_stage = 3;
            curXPos = 0;
        }
    }

    if (cur_stage == 3 && curXCycle == 0)
    {
        int8_t startPos = curXPos - TRAIL + 1;

        // Limiter
        if (startPos < 0)
            startPos = 0;

        for (int i = startPos; i <= curXPos; i++)
        {
            // This may be more efficient as a pointer to the tilemap?
            // SMS_debugPrintf("i: %d\n", i);
            if (i >= LOGO_TILES)
                break;

            int8_t mult = curXPos - i;

            if (mult < 0)
                mult = 0;

            mult = TRAIL - mult - 2;

            if (mult == -1)
            {
                SMS_setTileatXY(X_OFFSET + i, Y_OFFSET, 0);
                continue;
            }

            SMS_setTileatXY(X_OFFSET + i, Y_OFFSET, i + (LOGO_TILES * mult) + 1);
        }

        // Stage kick
        if (++curXPos > LOGO_TILES + TRAIL)
        {
            cur_stage = 4;
            curXPos = 0;
        }
    }

    if (cur_stage == 4)
    {
        SMS_VRAMmemsetW(XYtoADDR(11, 10), 0, (LOGO_TILES * 2));

        next_scene();
    }

    // Pause cycle for palette cycling
    if (++curXCycle == PALETTE_CYCLE)
        curXCycle = 0;
}

void logo_end(void)
{
    SMS_waitForVBlank();

    load_blank_tile(0);
    clear_tilemap(0);
}
