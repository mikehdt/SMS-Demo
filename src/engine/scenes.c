#include "../config_scenes.h"
#include "scenes.h"
#include <stdlib.h>

uint8_t cur_scene = DEFAULT, cur_stage;
uint16_t cur_frame;

void update_scene(void)
{
    scenes[cur_scene].update();
}

void next_scene(void)
{
    jump_to_scene(cur_scene + 1);
}

void jump_to_scene(uint8_t next_scene)
{
    if (cur_scene != next_scene)
    {
        scenes[cur_scene].end();

        if (next_scene >= MAX_SCENES)
            next_scene = 0;

        cur_frame = 0; // Should always reset this; Use cur_stage if splitting
        cur_scene = next_scene;
        scenes[cur_scene].init();
    }
}
