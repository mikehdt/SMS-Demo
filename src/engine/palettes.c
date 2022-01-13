#include "palettes.h"
#include "../libs/SMSlib.h"
#include "core.h"

unsigned char background_palette[16] = {
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00};

const unsigned char palette_black[16] = {
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00};

const unsigned char palette_white[16] = {
    0x3f, 0x3f, 0x3f, 0x3f,
    0x3f, 0x3f, 0x3f, 0x3f,
    0x3f, 0x3f, 0x3f, 0x3f,
    0x3f, 0x3f, 0x3f, 0x3f};

enum COLOR_COMPONENTS
{
    COLOR_R,
    COLOR_G,
    COLOR_B
};

unsigned char
fade_fragment(unsigned char current_color, unsigned char target_color)
{
    // Thought... so this flattens colours from immediate, rather than from end.
    // I wonder if there's a way to determine if say, the colour channel is a 1,
    // the target is 0 but it's only the first loop, don't flatten it until it
    // hits the third time?
    // Perhaps have a bitwise counter, which is reset on iteration 0?
    if (current_color > target_color)
        return current_color - 1;
    else if (current_color < target_color)
        return current_color + 1;
    return current_color;
}

unsigned char fade_to_color(unsigned char temporal_color, unsigned char target_color, int color_type)
{
    unsigned char r, g, b;

    r = getRFromRGB(temporal_color);
    g = getGFromRGB(temporal_color);
    b = getBFromRGB(temporal_color);

    switch (color_type)
    {
        case COLOR_R:
            r = fade_fragment(r, getRFromRGB(target_color));
            break;

        case COLOR_G:
            g = fade_fragment(g, getGFromRGB(target_color));
            break;

        case COLOR_B:
            b = fade_fragment(b, getBFromRGB(target_color));
            break;
    }

    return RGB(r, g, b);
}

void fade_to_color_loop(unsigned char *temporal_palette, unsigned char *target_palette, uint8_t color_type)
{
    for (uint8_t i = 0; i < 16; i++)
        temporal_palette[i] = fade_to_color(temporal_palette[i], target_palette[i], color_type);
}

// Temp, works for now -- make better later
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

    // temp hack
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
