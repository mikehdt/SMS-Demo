#include "palettes.h"
#include "../libs/SMSlib.h"
#include "core.h"

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

unsigned char fade_to_color(unsigned char temporal_color, unsigned char target_color, int color_type)
{
    unsigned char r, g, b;

    r = color_type == COLOR_R
            ? fade_fragment(getRFromRGB(temporal_color), getRFromRGB(target_color))
            : getRFromRGB(temporal_color);
    g = color_type == COLOR_G
            ? fade_fragment(getGFromRGB(temporal_color), getGFromRGB(target_color))
            : getGFromRGB(temporal_color);
    b = color_type == COLOR_B
            ? fade_fragment(getBFromRGB(temporal_color), getBFromRGB(target_color))
            : getBFromRGB(temporal_color);

    return RGB(r, g, b);
}

void fade_to_color_loop(unsigned char *temporal_palette, unsigned char *target_palette, uint8_t color_type)
{
    for (uint8_t i = 0; i < 16; i++)
        temporal_palette[i] = fade_to_color(temporal_palette[i], target_palette[i], color_type);
}

unsigned char color_array_in[9] = {
    COLOR_B, COLOR_B, COLOR_R,
    COLOR_B, COLOR_R, COLOR_G,
    COLOR_R, COLOR_G, COLOR_G};
unsigned char color_array_out[9] = {
    COLOR_G, COLOR_G, COLOR_R,
    COLOR_G, COLOR_R, COLOR_B,
    COLOR_R, COLOR_B, COLOR_B};

// To consider: palette offset / total change, instead of always being 0.
void fade_to_palette(unsigned char *target_palette, bool is_in)
{
    // Eventually, decouple this from blocking with wait_for_frame() calls
    uint8_t i, j;

    unsigned char temporal_palette[16];
    unsigned char *color_array;

    if (is_in)
        color_array = color_array_in;
    else
        color_array = color_array_out;

    memcpy(temporal_palette, background_palette, sizeof(temporal_palette));

    for (i = 0; i < 9; i++)

    {
        switch (color_array[i])
        {
            case COLOR_R:
                fade_to_color_loop(temporal_palette, target_palette, COLOR_R);
                break;

            case COLOR_G:
                fade_to_color_loop(temporal_palette, target_palette, COLOR_G);
                break;

            case COLOR_B:
                fade_to_color_loop(temporal_palette, target_palette, COLOR_B);
                break;
        }

        SMS_loadBGPalette(temporal_palette);

        for (j = 0; j < 6; j++)
            wait_for_frame();
    }

    // Copy the palette across to the background
    memcpy(background_palette, temporal_palette, sizeof(background_palette));
}

// An alternative take... doesn't do between palettes yet
void fade_from_black(unsigned char *target_palette)
{
    uint8_t i, j, frame_delay = 4;
    uint16_t progress_ratio, r, g, b;
    unsigned char temporal_palette[16];

    for (i = 0; i < 16; i++)
    {
        // There's no hardware fp on the Z80, so raise by 256 (left shift by
        // eight bits) to temporarily consider "decimals"
        progress_ratio = (i << 8) / (16 - 1);

        for (j = 0; j < 16; j++)
        {
            // Add 128 to make the "rounding" a little bit nicer, imho
            r = (getRFromRGB(target_palette[j]) * progress_ratio + 128) >> 8;
            g = (getGFromRGB(target_palette[j]) * progress_ratio + 128) >> 8;
            b = (getBFromRGB(target_palette[j]) * progress_ratio + 128) >> 8;

            temporal_palette[j] = RGB(r, g, b);
        }

        SMS_loadBGPalette(temporal_palette);

        for (j = 0; j < frame_delay; j++)
            wait_for_frame();
    }
}

void set_palette(unsigned char *palette, uint8_t palette_type)
{
    if (palette_type == PALETTE_BACKGROUND || palette_type == PALETTE_BOTH)
        SMS_loadBGPalette(palette);

    if (palette_type == PALETTE_SPRITE || palette_type == PALETTE_BOTH)
        SMS_loadSpritePalette(palette);
}
