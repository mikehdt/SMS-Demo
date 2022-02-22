#include "scenes.h"
#include "../libs/SMSlib.h"
#include "init_scenes.h"
#include <stdlib.h>

uint16_t frame_count;
int8_t current_scene = -1;

void update_scene(void)
{
    scenes[current_scene].update();
    frame_count++;
}

// TODO: Add ability to communicte a stage to the next scene's init
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
