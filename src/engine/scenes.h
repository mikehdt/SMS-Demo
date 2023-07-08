#ifndef _SCENES_H
#define _SCENES_H

#include <stdint.h>

void scene_update(void);
void transition_to_scene(uint8_t target_scene);
void wait_for_frame(void);
void next_scene(void);
void set_next_scene_stage(uint8_t target_stage);

void play_song(void);

#endif
