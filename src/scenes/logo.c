#include "logo.h"
#include "../assets2banks.h"
#include "../engine/global_constants.h"
#include "../engine/global_helpers.h"
#include "../engine/tilemap.h"
#include "../libs/SMSlib.h"

int8_t curXPos;
uint8_t stage, curXCycle, palette[16];

#define X_OFFSET 11
#define Y_OFFSET 10
#define LOGO_TILES 10
#define TRAIL 6
#define PALETTE_CYCLE 2

void logo_init(void)
{
    stage = 1;
    curXPos = 0;
    curXCycle = 0;

    palette[0] = 0x00;
    palette[1] = 0x00;
    palette[2] = 0x10;
    palette[3] = 0x20;
    palette[4] = 0x34;
    palette[5] = 0x38;
    palette[6] = 0x3d;
    palette[7] = 0x2d;
    palette[8] = 0x2e;
    palette[9] = 0x2f;
    palette[10] = 0x3f;
    palette[11] = 0x3f;
    // palette[1] = 0x3f;
    // palette[2] = 0x3f;
    // palette[3] = 0x3f;
    // palette[4] = 0x3f;
    // palette[5] = 0x3f;
    // palette[6] = 0x3f;
    // palette[7] = 0x3f;
    // palette[8] = 0x3f;
    // palette[9] = 0x3f;
    // palette[10] = 0x3f;
    // palette[11] = 0x3f;
    palette[12] = 0x3f;
    palette[13] = 0x3f;
    palette[14] = 0x3f;
    palette[15] = 0x3f;

    SMS_displayOff();

    wait_for_frame();
    clear_tilemap(0);

    SMS_loadBGPalette(palette);

    SMS_mapROMBank(da_mini_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(da_mini_tiles_psgcompr, 1);

    SMS_displayOn();
}

void logo_update(void)
{
    wait_for_frame();
    wait_for_frame();

    if (stage == 1)
    {
        for (int i = 0; i <= 16 - PALETTE_CYCLE; i++)
        {
            SMS_setBGPaletteColor(i + 1, palette[i + curXCycle]);
        }
    }
    else if (stage == 3)
    {
        for (int i = 0; i <= 16 - PALETTE_CYCLE; i++)
        {
            SMS_setBGPaletteColor(i + 1, palette[i + curXCycle + 1]);
        }
    }

    if (stage == 1 && curXCycle == 0)
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
            stage = 2;
            curXPos = 0;
        }
    }

    // Pause between fade in and out
    if (stage == 2 && ++curXPos > 16)
    {
        stage = 3;
        curXPos = 0;
    }

    if (stage == 3 && curXCycle == 0)
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
            stage = 4;
            curXPos = 0;
        }
    }

    // TEMP KILL PAUSE
    if (stage == 4)
    {
        SMS_debugPrintf("STAGE 4\n");
        stage = 1;
        curXPos = 0;
        SMS_VRAMmemsetW(XYtoADDR(11, 10), 0, (LOGO_TILES * 2));
        // Probs next scene
    }

    // Pause cycle for palette cycling
    if (++curXCycle == PALETTE_CYCLE)
        curXCycle = 0;
}

void logo_end(void)
{
    wait_for_frame();

    load_blank_tile(0);
    clear_tilemap(0);
}
