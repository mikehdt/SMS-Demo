#include "config_scenes.h"
#include "engine/scenes.h"
#include "scenes/default.h"
#include "scenes/logo.h"

Scenes scenes[MAX_SCENES];

// Idea: can I use a struct that's defined by the effects themselves to simplify this?
// IMPORTANT: All scenes must implement an init, update and end function.
void scenes_init(void)
{
    // Default
    scenes[SCENE_DEFAULT].init = default_init;
    scenes[SCENE_DEFAULT].update = default_update;
    scenes[SCENE_DEFAULT].end = default_end;

    scenes[SCENE_LOGO].init = logo_init;
    scenes[SCENE_LOGO].update = logo_update;
    scenes[SCENE_LOGO].end = logo_end;

    // Kick things off
    change_scene(SCENE_DEFAULT);
}
