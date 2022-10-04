#ifndef _GLOBAL_VARIABLES_H
#define _GLOBAL_VARIABLES_H

#include <stdint.h>

extern uint8_t frame_count; // Only good to keep track of as a tick, not time
extern uint8_t current_scene;

extern uint8_t current_rom_bank;
extern uint8_t current_music_bank;
extern uint8_t current_fx_bank;

extern uint8_t current_volume;
extern uint8_t target_volume;

#endif
