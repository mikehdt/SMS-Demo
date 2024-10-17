#ifndef _PALETTES_H
#define _PALETTES_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Note: these use a 0b binary notation bitmask, enabled by SDCC extensions.
// For some inane reason, 0b is not standard (although it was proposed in C99,
// rejected, and is finally due to be part of the spec... in 2023)
#define getRFromRGB(color) (color & 0b11)
#define getGFromRGB(color) ((color >> 2) & 0b11)
#define getBFromRGB(color) ((color >> 4) & 0b11)

enum PALETTE_TYPE
{
    PALETTE_BACKGROUND,
    PALETTE_SPRITE,
    PALETTE_BOTH
};

extern const unsigned char palette_black[16];
extern const unsigned char palette_white[16];

// void fade_to_palette(unsigned char *target_palette, unsigned char color_array_step);
void fade_to_black(unsigned char palette[16], unsigned char step);
void fade_sprite_to_black(unsigned char palette[16], unsigned char step);
void fade_from_black(unsigned char palette[16], unsigned char step);
void fade_to_white(unsigned char palette[16], unsigned char step);
void fade_from_white(unsigned char palette[16], unsigned char step);
void load_palette(unsigned char *palette, uint8_t palette_type);

void loadBGPaletteafterColorAddition(const void *palette, const unsigned char addition_color);

#endif
