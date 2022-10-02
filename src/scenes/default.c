#include "default.h"
#include "../engine/scenes.h"
#include "_scenes.h"

void default_scene_init(void) {}

void default_scene_update(void)
{
    transition_to_scene(SCENE_FIRE);
}

void default_scene_end(void) {}
