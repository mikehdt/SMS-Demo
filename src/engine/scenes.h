#ifndef _SCENES_H
#define _SCENES_H
#include <stdint.h>

void update_scene(void);
void transition_to_scene(uint8_t target_scene);
void waitForFrame(void);

#endif
