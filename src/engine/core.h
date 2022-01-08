#ifndef CORE_H
#define CORE_H

#include <stdbool.h>
#include <stdint.h>

#define SCREEN_COLUMNS 32
#define SCREEN_ROWS 30 // This might need to adjust based on PAL or NTSC?

void init_console(void);
void wait_for_frame(void);
void clear_tilemap(uint8_t tile);

#endif // CORE_H
