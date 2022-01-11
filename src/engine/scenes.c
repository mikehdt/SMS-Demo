#include "scenes.h"
#include "../scenes/default.h"
#include "../scenes/picture.h"
#include "core.h"

typedef void (*ptr_func)(void);

typedef struct
{
    ptr_func init;
    ptr_func update;
    ptr_func end;
} Scenes;

Scenes scenes[MAX_SCENES];

signed char current_scene = 0;

void null_func(void) {}

void init_scenes(void)
{
    // Default
    scenes[SCENE_DEFAULT].init = null_func;
    scenes[SCENE_DEFAULT].update = default_scene_update;
    scenes[SCENE_DEFAULT].end = null_func;

    scenes[SCENE_PICTURE].init = picture_scene_init;
    scenes[SCENE_PICTURE].update = picture_scene_update;
    scenes[SCENE_PICTURE].end = null_func;

    // Kick things off
    scenes[current_scene].init();
}

void update_scene(void)
{
    scenes[current_scene].update();
    wait_for_frame();
}

void transition_to_scene(signed char target_scene)
{
    if (current_scene != target_scene)
    {
        scenes[current_scene].end();
        current_scene = target_scene;
        scenes[current_scene].init();
    }
}
