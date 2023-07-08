#ifndef _GLOBAL_VARIABLES_H
#define _GLOBAL_VARIABLES_H

#include <stdint.h>

extern uint16_t frame_count;
extern uint8_t current_scene;
extern uint8_t current_scene_stage;
extern uint8_t target_scene_stage;

extern uint8_t current_rom_bank;
extern uint8_t current_music_bank;
extern uint8_t current_fx_bank;

extern uint8_t current_attenuation;
extern uint8_t target_attenuation;

#endif
