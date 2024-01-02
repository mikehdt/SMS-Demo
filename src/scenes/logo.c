#include "logo.h"
#include "../assets2banks.h"
#include "../engine/global_constants.h"
#include "../engine/global_helpers.h"
#include "../engine/tilemap.h"
#include "../libs/SMSlib.h"

uint8_t curXPos, curXCycle, curColorPos;
uint8_t palette[16];

#define LOGO_TILE_COUNT 10

void logo_init(void)
{
    curXPos = 0;
    curXCycle = 0;
    curColorPos = 0;

    palette[0] = 0x00;
    // palette[1] = 0x00;
    // palette[2] = 0x00;
    // palette[3] = 0x00;
    // palette[4] = 0x10;
    // palette[5] = 0x20;
    // palette[6] = 0x34;
    // palette[7] = 0x38;
    // palette[8] = 0x3d;
    // palette[9] = 0x2d;
    // palette[10] = 0x2e;
    // palette[11] = 0x2f;
    palette[1] = 0x3f;
    palette[2] = 0x3f;
    palette[3] = 0x3f;
    palette[4] = 0x3f;
    palette[5] = 0x3f;
    palette[6] = 0x3f;
    palette[7] = 0x3f;
    palette[8] = 0x3f;
    palette[9] = 0x3f;
    palette[10] = 0x3f;
    palette[11] = 0x3f;
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

    // Animate out first
    // if (curXPos > LOGO_TILE_COUNT + 4 + 1) // * 4)
    // {
    //     int subtr = LOGO_TILE_COUNT + 4 + 1;
    //     // for (int i = 0; i <= 12; i++)
    //     // {
    //     //     SMS_setBGPaletteColor(i + 1, palette[i + curXCycle]);
    //     // }

    //     if (curXCycle == 0)
    //     {
    //         for (int i = 0; i <= curXPos; i++)
    //         {
    //             int curMult = 6 - (curXPos - subtr + i);

    //             if (curMult < 0)
    //                 curMult = 0;

    //             SMS_debugPrintf("curXPos = %d, curMult = %d, i = %d\n", curXPos, curMult, i);

    //             if (i < LOGO_TILE_COUNT)
    //                 SMS_setTileatXY(i + 11, 10, i + (LOGO_TILE_COUNT * curMult));
    //         }

    //         curXPos++;
    //         SMS_debugPrintf("-----\n");
    //     }

    //     if (++curXCycle == 2)
    //         curXCycle = 0;

    //     if (curXPos > LOGO_TILE_COUNT * 4) // 8)
    //     {
    //         curXPos = 0;
    //         SMS_VRAMmemsetW(XYtoADDR(11, 10), 0, (LOGO_TILE_COUNT * 2));
    //         // Probs next scene
    //     }

    //     return;
    // }

    // // Hold second
    // if (curXPos > LOGO_TILE_COUNT + 4 + 1) // Add the palette timing
    // {
    //     curXPos++;

    //     return;
    // }

    // Animate in third
    // for (int i = 0; i <= 12; i++)
    // {
    //     SMS_setBGPaletteColor(i + 1, palette[i + curXCycle]);
    // }

    if (curXCycle == 0)
    {
        // Life-changing debug statement
        // SMS_debugPrintf("curTile = %d, curMult = %d, i = %d\n", i + (LOGO_TILE_COUNT * curMult) + 1, curMult, i);
        for (int i = curXPos; i < curXPos + 4; i++)
        {
            SMS_debugPrintf("i: %d\n", i);

            if (i < LOGO_TILE_COUNT)
                SMS_setTileatXY(11 + i, 10, i + 1);
        }

        curXPos++;
    }

    if (++curXCycle == 2)
        curXCycle = 0;

    // TEMP
    if (curXPos > LOGO_TILE_COUNT * 4) // 8)
    {
        SMS_debugPrintf("=== RESET ===\n");

        curXPos = 0;
        SMS_VRAMmemsetW(XYtoADDR(11, 10), 0, (LOGO_TILE_COUNT * 2));
        // Probs next scene
    }
}

void logo_end(void)
{
    wait_for_frame();

    load_blank_tile(0);
    clear_tilemap(0);
}
