#include "scenes.h"
#include "../libs/SMSlib.h"
#include "../scenes/default.h"
#include "../scenes/fire.h"
#include "../scenes/grid.h"
#include "../scenes/intro.h"
#include "../scenes/particles.h"
#include "../scenes/plasma.h"
#include "../scenes/scroller.h"
#include "../scenes/sineline.h"
#include "../scenes/sphere.h"
#include "../scenes/type.h"
#include <stdlib.h>

uint16_t frame_count;
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

    scenes[SCENE_INTRO].init = intro_scene_init;
    scenes[SCENE_INTRO].update = intro_scene_update;

    scenes[SCENE_PARTICLES].init = particles_scene_init;
    scenes[SCENE_PARTICLES].update = particles_scene_update;
    scenes[SCENE_PARTICLES].end = particles_scene_end;

    scenes[SCENE_PLASMA].init = plasma_scene_init;
    scenes[SCENE_PLASMA].update = plasma_scene_update;

    scenes[SCENE_SCROLLER].init = scroller_scene_init;
    scenes[SCENE_SCROLLER].update = scroller_scene_update;
    scenes[SCENE_SCROLLER].end = scroller_scene_end;

    scenes[SCENE_SINELINE].init = sineline_scene_init;
    scenes[SCENE_SINELINE].update = sineline_scene_update;
    scenes[SCENE_SINELINE].end = sineline_scene_end;

    scenes[SCENE_SPHERE].init = sphere_scene_init;
    scenes[SCENE_SPHERE].update = sphere_scene_update;
    scenes[SCENE_SPHERE].end = sphere_scene_end;

    scenes[SCENE_TYPE].init = type_scene_init;
    scenes[SCENE_TYPE].update = type_scene_update;
    scenes[SCENE_TYPE].end = type_scene_end;

    // Kick things off
    transition_to_scene(SCENE_DEFAULT);
}

void update_scene(void)
{
    // Need to handle this better
    if (SMS_getKeysHeld() & PORT_A_KEY_1)
    {
        // "Debounce" the button press as it were... this is a bit hacky
        while (SMS_getKeysHeld() != 0x0000)
            SMS_waitForVBlank();

        if (current_scene + 1 >= MAX_SCENES)
            transition_to_scene(1);
        else
            transition_to_scene(current_scene + 1);
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
