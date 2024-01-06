#ifndef _SCENES_H
#define _SCENES_H

#include <stdint.h>

extern uint8_t current_scene, current_stage;

void update_scene(void);
void next_scene(void);
void jump_to_scene(uint8_t next_scene);

#endif
