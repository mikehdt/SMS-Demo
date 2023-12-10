#ifndef _SCENES_H
#define _SCENES_H

#include <stdint.h>

void update_scene(void);
void next_scene(void);
void change_scene_to(uint8_t next_scene);
void wait_for_frame(void);

#endif
