#include "scenes.h"
#include "../libs/SMSlib.h"
#include "../scenes/default.h"
#include "../scenes/fire.h"
#include "../scenes/grid.h"
#include "../scenes/particles.h"
#include "../scenes/plasma.h"
#include "../scenes/sineline.h"
#include "../scenes/sphere.h"
#include "../scenes/type.h"
#include <stdlib.h>

uint16_t frame_count, keys_released;
int8_t current_scene = -1;

typedef void (*ptr_func)(void);

typedef struct
{
    ptr_func init;
    ptr_func update;
    ptr_func end;
} Scenes;

Scenes scenes[MAX_SCENES];

void init_scenes(void)
{
    // Default
    scenes[SCENE_DEFAULT].update = default_scene_update;

    scenes[SCENE_FIRE].init = fire_scene_init;
    scenes[SCENE_FIRE].update = fire_scene_update;

    scenes[SCENE_GRID].init = grid_scene_init;
    scenes[SCENE_GRID].update = grid_scene_update;

    scenes[SCENE_PARTICLES].init = particles_scene_init;
    scenes[SCENE_PARTICLES].update = particles_scene_update;
    scenes[SCENE_PARTICLES].end = particles_scene_end;

    scenes[SCENE_PLASMA].init = plasma_scene_init;
    scenes[SCENE_PLASMA].update = plasma_scene_update;

    scenes[SCENE_SINELINE].init = sineline_scene_init;
    scenes[SCENE_SINELINE].update = sineline_scene_update;
    scenes[SCENE_SINELINE].end = sineline_scene_end;

    scenes[SCENE_SPHERE].init = sphere_scene_init;
    scenes[SCENE_SPHERE].update = sphere_scene_update;
    scenes[SCENE_SPHERE].end = sphere_scene_end;

    scenes[SCENE_TYPE].init = type_scene_init;
    scenes[SCENE_TYPE].update = type_scene_update;

    // Kick things off
    transition_to_scene(SCENE_DEFAULT);
}

void update_scene(void)
{
    keys_released = SMS_getKeysReleased();
    if (keys_released & PORT_A_KEY_1)
    {
        if (current_scene == SCENE_PARTICLES)
            transition_to_scene(SCENE_SPHERE);
        else if (current_scene == SCENE_SPHERE)
            transition_to_scene(SCENE_SINELINE);
        else if (current_scene == SCENE_SINELINE)
            transition_to_scene(SCENE_PARTICLES);
        else // Fallback
            transition_to_scene(SCENE_PARTICLES);

        return;
    }

    scenes[current_scene].update();
    frame_count++;
}

void transition_to_scene(int8_t target_scene)
{
    if (current_scene != target_scene)
    {
        if (scenes[current_scene].end != NULL)
            scenes[current_scene].end();

        current_scene = target_scene;
        frame_count = 0;

        if (scenes[current_scene].init != NULL)
            scenes[current_scene].init();
    }
}
