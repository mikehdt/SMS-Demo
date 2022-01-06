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

// To consider: palette offset / total change, instead of always being 0.
void fade_to_palette(unsigned char *target_palette, unsigned char num_colors, unsigned char frame_delay)
{
    uint8_t i, j;
    unsigned char r, g, b, target;
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
            r = getRFromRGB(temporal_palette[j]);
            g = getGFromRGB(temporal_palette[j]);
            b = getBFromRGB(temporal_palette[j]);
            target = getBFromRGB(target_palette[j]);

            if (b > target)
                b--;
            else if (b < target)
                b++;

            temporal_palette[j] = RGB(r, g, b);
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
            r = getRFromRGB(temporal_palette[j]);
            g = getGFromRGB(temporal_palette[j]);
            b = getBFromRGB(temporal_palette[j]);
            target = getRFromRGB(target_palette[j]);

            if (r > target)
                r--;
            else if (r < target)
                r++;

            temporal_palette[j] = RGB(r, g, b);
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
            r = getRFromRGB(temporal_palette[j]);
            g = getGFromRGB(temporal_palette[j]);
            b = getBFromRGB(temporal_palette[j]);
            target = getGFromRGB(target_palette[j]);

            if (g > target)
                g--;
            else if (g < target)
                g++;

            temporal_palette[j] = RGB(r, g, b);
        }

        SMS_loadBGPalette(temporal_palette);

        for (j = 0; j < frame_delay; j++)
            wait_for_frame();
    }
}

void fade_from_black(unsigned char *target_palette)
{
    uint8_t i, j, frame_delay = 4, num_steps = 16;
    uint16_t progress_ratio, r, g, b;
    unsigned char temporal_palette[16];

    for (i = 0; i < num_steps; i++)
    {
        progress_ratio = (i * 256) / (num_steps - 1);

        for (j = 0; j < 16; j++)
        {
            r = (getRFromRGB(target_palette[j]) * progress_ratio + 128) / 256;
            g = (getGFromRGB(target_palette[j]) * progress_ratio + 128) / 256;
            b = (getBFromRGB(target_palette[j]) * progress_ratio + 128) / 256;

            temporal_palette[j] = RGB(r, g, b);
        }

        SMS_loadBGPalette(temporal_palette);

        for (j = 0; j < frame_delay; j++)
            wait_for_frame();
    }
}

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
    uint8_t palette_white[16] = {0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f};
    palette_set(palette_white, paletteType);
}

void palette_set_black(uint8_t paletteType)
{
    uint8_t palette_black[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    palette_set(palette_black, paletteType);
}
