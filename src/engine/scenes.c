#include "scenes.h"
#include "../libs/SMSlib.h"
#include "../scenes/_scenes.h"
#include <stdlib.h>

// I want to abstract these somewhere, maybe to globals? Then have these fns
// as separate concerns
uint8_t frame_count; // Only good to keep track of as a tick, not time
uint8_t current_scene = 0;

void update_scene(void)
{
    scenes[current_scene].update();
    frame_count++;
}

// TODO: Add ability to communicate a stage to the next scene's init?
void transition_to_scene(uint8_t target_scene)
{
    if (current_scene != target_scene)
    {
        scenes[current_scene].end();

        current_scene = target_scene;
        frame_count = 0;

        scenes[current_scene].init();
    }
}
