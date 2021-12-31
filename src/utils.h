#ifndef UTILS_H
#define UTILS_H
#include <stdint.h>

#define SCREEN_ROWS 30 // This might need to adjust based on PAL or NTSC?
#define SCREEN_COLUMNS 32

#define PALETTE_BOTH 0
#define PALETTE_BACKGROUND 1
#define PALETTE_SPRITE 2

#define FADE_STEPS 16

void wait_for_frame(void);
void clear_tilemap(uint8_t tile);

void palette_make_fade(unsigned char *new_palette);
void palette_fadein_handler(uint8_t paletteType);
void palette_set_white(uint8_t paletteType);
void palette_set_black(uint8_t paletteType);

#endif // UTILS_H
