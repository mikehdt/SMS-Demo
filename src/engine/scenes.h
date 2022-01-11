#ifndef SCENES_H
#define SCENES_H
#include <stdint.h>

extern uint16_t frame_count;

void init_scenes(void);
void update_scene(void);

void null_func(void);

void transition_to_scene(int8_t target_scene);

enum SCENES
{
    SCENE_DEFAULT = 0,
    SCENE_PICTURE,
    MAX_SCENES // This creates a counter for us, as long as it remains last :)
};

#endif // SCENES_H
