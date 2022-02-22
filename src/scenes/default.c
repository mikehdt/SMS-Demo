#include "default.h"
#include "../engine/init_scenes.h"
#include "../engine/scenes.h"

void default_scene_update(void)
{
    transition_to_scene(SCENE_FIRE);
}
