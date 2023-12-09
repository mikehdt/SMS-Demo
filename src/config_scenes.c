#include "config_scenes.h"
#include "scenes/default.h"
#include "scenes/fire.h"
#include "scenes/logo.h"
#include "scenes/plasma.h"

Scenes scenes[MAX_SCENES];

// Idea: can I use a struct that's defined by the effects themselves to simplify this?
// IMPORTANT: All scenes must implement an init, update and end function.
void scenes_init(void)
{
    // Default
    scenes[SCENE_DEFAULT].init = default_init;
    scenes[SCENE_DEFAULT].update = default_update;
    scenes[SCENE_DEFAULT].end = default_end;

    scenes[SCENE_FIRE].init = fire_init;
    scenes[SCENE_FIRE].update = fire_update;
    scenes[SCENE_FIRE].end = fire_end;

    scenes[SCENE_LOGO].init = logo_init;
    scenes[SCENE_LOGO].update = logo_update;
    scenes[SCENE_LOGO].end = logo_end;

    scenes[SCENE_PLASMA].init = plasma_init;
    scenes[SCENE_PLASMA].update = plasma_update;
    scenes[SCENE_PLASMA].end = plasma_end;
}
