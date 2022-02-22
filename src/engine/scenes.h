#ifndef _SCENES_H
#define _SCENES_H
#include <stdint.h>

extern uint16_t frame_count;
extern int8_t current_scene;

void init_scenes(void);
void update_scene(void);

void transition_to_scene(int8_t target_scene);

enum SCENES
{
    SCENE_DEFAULT = 0,
    SCENE_FIRE,
    SCENE_GRID,
    // SCENE_INTRO,
    SCENE_PARTICLES,
    SCENE_PLASMA,
    SCENE_SCROLLER,
    SCENE_SINELINE,
    SCENE_SPHERE,
    SCENE_TYPE,
    MAX_SCENES // This creates a max counter for us, so long as it's last :)
};

#endif
