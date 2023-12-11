#include "scenes.h"
#include "../config_scenes.h"
#include "../libs/SMSlib.h"
#include "audio.h"
#include "global_variables.h"
#include <stdlib.h>

void update_scene(void)
{
    scenes[current_scene].update();
    frame_count++;
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

        frame_count = 0;
        current_scene = next_scene;

        scenes[current_scene].init();
    }
}

void wait_for_frame(void)
{
    update_audio();
    SMS_waitForVBlank();
}
