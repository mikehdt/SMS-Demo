#include "scenes.h"
#include "../config_scenes.h"
#include <stdlib.h>

uint8_t current_scene = 0, current_stage;

void update_scene(void)
{
    scenes[current_scene].update();
}

void next_scene(void)
{
    jump_to_scene(current_scene + 1);
}

void jump_to_scene(uint8_t next_scene)
{
    if (current_scene != next_scene)
    {
        scenes[current_scene].end();

        if (next_scene >= MAX_SCENES)
            next_scene = 0;

        current_scene = next_scene;
        scenes[current_scene].init();
    }
}
