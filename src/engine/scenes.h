#ifndef _SCENES_H
#define _SCENES_H
#include <stdint.h>

extern uint8_t frame_count;
extern uint8_t current_scene;

void update_scene(void);
void transition_to_scene(uint8_t target_scene);

#endif
