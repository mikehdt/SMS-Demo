#ifndef CORE_H
#define CORE_H

#include <stdbool.h>
#include <stdint.h>

#define SCREEN_COLUMNS 32
#define SCREEN_ROWS 24 // This might need to adjust based on PAL or NTSC?
#define SCREEN_ROWS_FULL 28

void init_console(void);
void wait_for_vblank(void);
void clear_tilemap(uint16_t tile);

#endif // CORE_H
