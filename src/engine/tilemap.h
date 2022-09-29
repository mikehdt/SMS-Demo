#ifndef _TILEMAP_H
#define _TILEMAP_H
#include <stdbool.h>
#include <stdint.h>

void load_blank_tile(uint16_t tilePos);
void clear_tilemap(uint16_t tilePos);
void init_sprites(uint8_t spriteMode, bool useFirstHalfTiles);
void clear_sprites(void);

#endif
