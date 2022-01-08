#include "palettes.h"
#include "../libs/SMSlib.h"
#include "core.h"
#include <stdlib.h>
#include <string.h>

unsigned char background_palette[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

#define COLOR_R 0
#define COLOR_G 1
#define COLOR_B 2

unsigned char fade_fragment(unsigned char current_color, unsigned char target_color)
{
    if (current_color > target_color)
        return current_color - 1;
    else if (current_color < target_color)
        return current_color + 1;
    return current_color;
}

unsigned char fade_to_color(unsigned char temporal_color, unsigned char target_color, int subject_color)
{
    unsigned char r, g, b;

    r = subject_color == COLOR_R
            ? fade_fragment(getRFromRGB(temporal_color), getRFromRGB(target_color))
            : getRFromRGB(temporal_color);
    g = subject_color == COLOR_G
            ? fade_fragment(getGFromRGB(temporal_color), getGFromRGB(target_color))
            : getGFromRGB(temporal_color);
    b = subject_color == COLOR_B
            ? fade_fragment(getBFromRGB(temporal_color), getBFromRGB(target_color))
            : getBFromRGB(temporal_color);

    return RGB(r, g, b);
}

// To consider: palette offset / total change, instead of always being 0.
void fade_to_palette(unsigned char *target_palette, unsigned char num_colors, uint8_t frame_delay)
{
    uint8_t i, j;
    unsigned char temporal_palette[16];

    // for (i = 0; i < num_colors; i++)
    //     temporal_palette[i] = background_palette[i];
    memcpy(temporal_palette, background_palette, sizeof(temporal_palette));

    // Blue
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < num_colors; j++)
            temporal_palette[j] = fade_to_color(temporal_palette[j], target_palette[j], COLOR_B);

        SMS_loadBGPalette(temporal_palette);

        for (j = 0; j < frame_delay; j++)
            wait_for_frame();
    }

    // Red
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < num_colors; j++)
            temporal_palette[j] = fade_to_color(temporal_palette[j], target_palette[j], COLOR_R);

        SMS_loadBGPalette(temporal_palette);

        for (j = 0; j < frame_delay; j++)
            wait_for_frame();
    }

    // Green
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < num_colors; j++)
            temporal_palette[j] = fade_to_color(temporal_palette[j], target_palette[j], COLOR_G);

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
