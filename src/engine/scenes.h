#ifndef SCENES_H
#define SCENES_H
#include <stdint.h>

extern uint16_t frame_count;
extern unsigned int keys_released;

void init_scenes(void);
void update_scene(void);

void transition_to_scene(int8_t target_scene);

enum SCENES
{
    SCENE_DEFAULT = 0,
    SCENE_PICTURE,
    SCENE_SINELINE,
    SCENE_SPHERE,
    MAX_SCENES // This creates a counter for us, as long as it remains last :)
};

#endif // SCENES_H
