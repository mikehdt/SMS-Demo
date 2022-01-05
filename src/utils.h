#ifndef UTILS_H
#define UTILS_H
#include <stdint.h>

#define SCREEN_COLUMNS 32
#define SCREEN_ROWS 30 // This might need to adjust based on PAL or NTSC?

#define PALETTE_BOTH 0
#define PALETTE_BACKGROUND 1
#define PALETTE_SPRITE 2

void wait_for_frame(void);
void clear_tilemap(uint8_t tile);

void fade_to_palette(unsigned char *target_palette, unsigned char num_colors, unsigned char frame_delay);
void palette_set_white(uint8_t paletteType);
void palette_set_black(uint8_t paletteType);

#endif // UTILS_H
