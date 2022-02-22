#ifndef _SCENES_H
#define _SCENES_H
#include <stdint.h>

extern uint16_t frame_count;
extern int8_t current_scene;

void update_scene(void);
void transition_to_scene(int8_t target_scene);

#endif
