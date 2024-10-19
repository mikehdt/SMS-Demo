#include "palettes.h"
#include "../libs/SMSlib.h"

// Palette reference: https://www.smspower.org/maxim/HowToProgram/Palette

// Eventually, decouple these fns from blocking with wait for vblank calls
// Also tidy this into several different helper functions

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

/*
COLOR_G, COLOR_G, COLOR_R,
COLOR_G, COLOR_R, COLOR_B,
COLOR_R, COLOR_B, COLOR_B
*/

// White
const unsigned char color_increase_in[10] = {RGB(0, 0, 0),
                                             RGB(1, 0, 0), RGB(2, 0, 0), RGB(2, 1, 0),
                                             RGB(3, 1, 0), RGB(3, 2, 0), RGB(3, 2, 1),
                                             RGB(3, 3, 1), RGB(3, 3, 2), RGB(3, 3, 3)};
const unsigned char color_increase_out[10] = {RGB(3, 3, 3), RGB(3, 2, 3), RGB(3, 2, 2),
                                              RGB(2, 2, 2), RGB(2, 1, 2), RGB(2, 1, 1),
                                              RGB(1, 1, 1), RGB(1, 0, 1), RGB(1, 0, 0),
                                              RGB(0, 0, 0)};

// Black
const unsigned char color_reduction_out[10] = {RGB(0, 0, 0),
                                               RGB(0, 1, 0), RGB(0, 2, 0), RGB(1, 2, 0),
                                               RGB(1, 3, 0), RGB(2, 3, 0), RGB(2, 3, 1),
                                               RGB(3, 3, 1), RGB(3, 3, 2), RGB(3, 3, 3)};
const unsigned char color_reduction_in[10] = {RGB(3, 3, 3), RGB(3, 3, 2), RGB(3, 3, 1),
                                              RGB(2, 3, 1), RGB(2, 3, 0), RGB(1, 3, 0),
                                              RGB(1, 2, 0), RGB(0, 2, 0), RGB(0, 1, 0),
                                              RGB(0, 0, 0)};

// These could probably be abstracted back to their in-use place, even if convenient
void fade_from_white(unsigned char palette[16], unsigned char step)
{
    SMS_loadBGPaletteafterColorAddition(palette, color_increase_out[step]);
}

void fade_to_white(unsigned char palette[16], unsigned char step)
{
    SMS_loadBGPaletteafterColorAddition(palette, color_increase_in[step]);
}

void fade_from_black(unsigned char palette[16], unsigned char step)
{
    SMS_loadBGPaletteafterColorSubtraction(palette, color_reduction_in[step]);
}

void fade_to_black(unsigned char palette[16], unsigned char step)
{
    SMS_loadBGPaletteafterColorSubtraction(palette, color_reduction_out[step]);
}

// Urgh
void fade_sprite_from_black(unsigned char palette[16], unsigned char step)
{
    SMS_loadSpritePaletteafterColorSubtraction(palette, color_reduction_in[step]);
}

void fade_sprite_to_black(unsigned char palette[16], unsigned char step)
{
    SMS_loadSpritePaletteafterColorSubtraction(palette, color_reduction_out[step]);
}

// unsigned char temporal_palette[16];

// enum COLOR_COMPONENTS
// {
//     COLOR_R,
//     COLOR_G,
//     COLOR_B
// };

// unsigned char fade_fragment(unsigned char current_color, unsigned char target_color)
// {
//     // So this routine flattens colours from immediate, rather than from end.
//     //
//     // I wonder if there's a way to determine if say, the colour channel is a 1,
//     // the target is 0 but it's only the first loop, don't flatten it until it
//     // hits the third time?
//     //
//     // Perhaps have a bitwise counter, which is reset on iteration 0?
//     if (current_color > target_color)
//         return current_color - 1;
//     else if (current_color < target_color)
//         return current_color + 1;

//     return current_color;
// }

// unsigned char fade_to_color(unsigned char temporal_color, unsigned char target_color, int color_type)
// {
//     unsigned char r, g, b;

//     r = (color_type == COLOR_R)
//             ? fade_fragment(getRFromRGB(temporal_color), getRFromRGB(target_color))
//             : getRFromRGB(temporal_color);
//     g = (color_type == COLOR_G)
//             ? fade_fragment(getGFromRGB(temporal_color), getGFromRGB(target_color))
//             : getGFromRGB(temporal_color);
//     b = (color_type == COLOR_B)
//             ? fade_fragment(getBFromRGB(temporal_color), getBFromRGB(target_color))
//             : getBFromRGB(temporal_color);

//     return RGB(r, g, b);
// }

// void fade_to_color_loop(unsigned char *target_palette, unsigned char color_type)
// {
//     char i = 0;

//     do
//     {
//         temporal_palette[i++] = fade_to_color(temporal_palette[i], target_palette[i], color_type);
//     } while (i++ < 16);
// }

// const unsigned char color_array_in[9] = {
//     COLOR_B, COLOR_B, COLOR_R,
//     COLOR_B, COLOR_R, COLOR_G,
//     COLOR_R, COLOR_G, COLOR_G};

// const unsigned char color_array_out[9] = {
//     COLOR_G, COLOR_G, COLOR_R,
//     COLOR_G, COLOR_R, COLOR_B,
//     COLOR_R, COLOR_B, COLOR_B};

// // To consider: palette offset / total change, instead of always being 0.
// void fade_to_palette(unsigned char *target_palette, unsigned char color_array_step)
// {
//     fade_to_color_loop(target_palette, color_array_step);
//     SMS_loadBGPalette(temporal_palette);
// }

// void set_background_to_temporal(void)
// {
//     // Copy the palette across to the background
//     memcpy(background_palette, temporal_palette, sizeof(background_palette));
// }

// An alternative take... doesn't do between palettes yet
void fade_from_black_alt(unsigned char *target_palette)
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

        // Need to decouple this delay somehow...
        for (j = 0; j < frame_delay; j++)
            SMS_waitForVBlank();
    }
}

void load_palette(unsigned char *palette, uint8_t palette_type)
{
    if (palette_type == PALETTE_BACKGROUND || palette_type == PALETTE_BOTH)
    {
        SMS_loadBGPalette(palette);
        // memcpy(background_palette, palette, sizeof(background_palette));
    }

    if (palette_type == PALETTE_SPRITE || palette_type == PALETTE_BOTH)
    {
        SMS_loadSpritePalette(palette);
        // memcpy(sprite_palette, palette, sizeof(background_palette));
    }
}
