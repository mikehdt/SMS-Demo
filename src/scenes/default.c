#include "default.h"
#include "../engine/init_scenes.h"
#include "../engine/update_scenes.h"

void default_scene_update(void)
{
    transition_to_scene(SCENE_TYPE);
}
