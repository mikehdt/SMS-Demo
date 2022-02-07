#ifndef SCENES_H
#define SCENES_H
#include <stdint.h>

extern uint16_t frame_count, keys_released;

void init_scenes(void);
void update_scene(void);

void transition_to_scene(int8_t target_scene);

enum SCENES
{
    SCENE_DEFAULT = 0,
    SCENE_FIRE,
    SCENE_GRID,
    SCENE_PARTICLES,
    SCENE_PLASMA,
    SCENE_SINELINE,
    SCENE_SPHERE,
    SCENE_TYPE,
    MAX_SCENES // This creates a counter for us, as long as it remains last :)
};

#endif
