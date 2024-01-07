#ifndef _SCENES_H
#define _SCENES_H

#include <stdint.h>

// cur_stage and cur_frame are general common counters that scenes can
// use, with values managed internally in each scene.
// cur_stage is intended for which action sequence within a scene is happening
// cur_frame is intended for counting time until something is triggered
extern uint8_t cur_scene, cur_stage;
extern uint16_t cur_frame;

void update_scene(void);
void next_scene(void);
void jump_to_scene(uint8_t next_scene);

#endif
