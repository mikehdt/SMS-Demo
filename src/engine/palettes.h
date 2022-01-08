#ifndef PALETTES_H
#define PALETTES_H

#include <stdint.h>

#define PALETTE_BOTH 0
#define PALETTE_BACKGROUND 1
#define PALETTE_SPRITE 2

// Note: these use a 0b binary notation bitmask, enabled by SDCC extensions.
// For some inane reason, 0b is not standard (although it was proposed in C99,
// rejected, and is finally due to be part of the spec... in 2023)
#define getRFromRGB(color) (color & 0b11)
#define getGFromRGB(color) ((color >> 2) & 0b11)
#define getBFromRGB(color) ((color >> 4) & 0b11)

void fade_to_palette(unsigned char *target_palette, unsigned char num_colors, unsigned char frame_delay);
void fade_from_black(unsigned char *target_palette);
void palette_set_white(uint8_t paletteType);
void palette_set_black(uint8_t paletteType);

#endif // PALETTES_H
