#include "config_scenes.h"
#include "../engine/scenes.h"
#include "default.h"
// #include "fire.h"
#include "logo.h"
// #include "particles.h"
// #include "plasma.h"
// #include "scroller.h"
// #include "sineline.h"
// #include "sphere.h"
// #include "type.h"

Scenes scenes[MAX_SCENES];

// Idea: can I use a struct that's defined by the effects themselves to simplify this?
// IMPORTANT: All scenes must implement an init, update and end function.
void scenes_init(void)
{
    // Default
    scenes[SCENE_DEFAULT].init = default_scene_init;
    scenes[SCENE_DEFAULT].update = default_scene_update;
    scenes[SCENE_DEFAULT].end = default_scene_end;

    scenes[SCENE_LOGO].init = logo_scene_init;
    scenes[SCENE_LOGO].update = logo_scene_update;
    scenes[SCENE_LOGO].end = logo_scene_end;

    // Kick things off
    transition_to_scene(SCENE_DEFAULT);
}
