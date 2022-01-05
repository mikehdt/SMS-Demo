#include "utils.h"
#include "libs/SMSlib.h"
#include <stdlib.h>

void wait_for_frame(void)
{
    SMS_waitForVBlank();
    SMS_copySpritestoSAT(); // Update any sprite shenanigans
}

void clear_tilemap(uint8_t tile)
{
    // From sverx, a more efficient method
    SMS_VRAMmemsetW(XYtoADDR(0, 0), tile, SCREEN_ROWS * SCREEN_COLUMNS * 2);
}

unsigned char background_palette[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// Note: these use a 0b binary notation bitmask, enabled by the SDCC extensions.
// For some inane reason, this is not a standard part of C99 (although it was
// proposed, rejected, and is finally due to be part of the spec... in 2023)
#define getRFromRGB(color) color & 0b11
#define getGFromRGB(color) color >> 2 & 0b11
#define getBFromRGB(color) color >> 4 & 0b11

void fade_to_palette(unsigned char *target_palette, unsigned char num_colors, unsigned char frame_delay)
{
    uint8_t i, j;
    unsigned char rPart, gPart, bPart, tPart;
    unsigned char temporal_palette[16];

    for (i = 0; i < num_colors; i++)
    {
        temporal_palette[i] = background_palette[i];
    }

    SMS_loadBGPalette(background_palette);

    // Blue
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < num_colors; j++)
        {
            rPart = getRFromRGB(temporal_palette[j]);
            gPart = getGFromRGB(temporal_palette[j]);
            bPart = getBFromRGB(temporal_palette[j]);
            tPart = getBFromRGB(target_palette[j]);

            if (bPart > tPart)
                bPart--;
            else if (bPart < tPart)
                bPart++;

            temporal_palette[j] = RGB(rPart, gPart, bPart);
        }

        SMS_loadBGPalette(temporal_palette);

        for (j = 0; j < frame_delay; j++)
            wait_for_frame();
    }

    // Red
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < num_colors; j++)
        {
            rPart = getRFromRGB(temporal_palette[j]);
            gPart = getGFromRGB(temporal_palette[j]);
            bPart = getBFromRGB(temporal_palette[j]);
            tPart = getRFromRGB(target_palette[j]);

            if (rPart > tPart)
                rPart--;
            else if (rPart < tPart)
                rPart++;

            temporal_palette[j] = RGB(rPart, gPart, bPart);
        }

        SMS_loadBGPalette(temporal_palette);

        for (j = 0; j < frame_delay; j++)
            wait_for_frame();
    }

    // Green
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < num_colors; j++)
        {
            rPart = getRFromRGB(temporal_palette[j]);
            gPart = getGFromRGB(temporal_palette[j]);
            bPart = getBFromRGB(temporal_palette[j]);
            tPart = getGFromRGB(target_palette[j]);

            if (gPart > tPart)
                gPart--;
            else if (gPart < tPart)
                gPart++;

            temporal_palette[j] = RGB(rPart, gPart, bPart);
        }

        SMS_loadBGPalette(temporal_palette);

        for (j = 0; j < frame_delay; j++)
            wait_for_frame();
    }

    // setBGPalette(target_palette, num_colors);
}

// void palette_make_fade(unsigned char *new_palette)
// {
//     // Generate fade lookup ... not sure this is working properly yet
//     for (uint8_t i = 0; i < FADE_STEPS; i++)
//     {
//         for (uint8_t j = 0; j < 16; j++)
//         {
//             unsigned char r, g, b;
//             uint16_t progress_ratio = (i + 1) * 256 / FADE_STEPS;

//             r = setRToRGB(getRFromRGB(new_palette[j]) * progress_ratio / 256);
//             g = setGToRGB(getGFromRGB(new_palette[j]) * progress_ratio / 256);
//             b = setBToRGB(getBFromRGB(new_palette[j]) * progress_ratio / 256);

//             fade_palette[i][j] = r | g | b;
//         }
//     }
// }

void palette_set(const void *palette, uint8_t paletteType)
{
    // Background palette
    if (paletteType == PALETTE_BOTH || paletteType == PALETTE_BACKGROUND)
        SMS_loadBGPalette(palette);

    // Sprite palette
    if (paletteType == PALETTE_BOTH || paletteType == PALETTE_SPRITE)
        SMS_loadSpritePalette(palette);
}

void palette_set_white(uint8_t paletteType)
{
    uint8_t palette_white[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    palette_set(palette_white, paletteType);
}

void palette_set_black(uint8_t paletteType)
{
    uint8_t palette_black[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    palette_set(palette_black, paletteType);
}
