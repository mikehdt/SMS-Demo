#ifndef PALETTES_H
#define PALETTES_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define PALETTE_BOTH 0
#define PALETTE_BACKGROUND 1
#define PALETTE_SPRITE 2

// Note: these use a 0b binary notation bitmask, enabled by SDCC extensions.
// For some inane reason, 0b is not standard (although it was proposed in C99,
// rejected, and is finally due to be part of the spec... in 2023)
#define getRFromRGB(color) (color & 0b11)
#define getGFromRGB(color) ((color >> 2) & 0b11)
#define getBFromRGB(color) ((color >> 4) & 0b11)

uint8_t palette_black[16] = {
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00};

uint8_t palette_white[16] = {
    0x3f, 0x3f, 0x3f, 0x3f,
    0x3f, 0x3f, 0x3f, 0x3f,
    0x3f, 0x3f, 0x3f, 0x3f,
    0x3f, 0x3f, 0x3f, 0x3f};

void fade_to_palette(unsigned char *target_palette, bool is_in);
void fade_from_black(unsigned char *target_palette);
void set_palette(unsigned char *palette, uint8_t palette_type);

#endif // PALETTES_H
