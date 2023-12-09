#include "scenes.h"
// #include "../libs/PSGlib.h"
#include "../config_scenes.h"
#include "../libs/SMSlib.h"
#include "global_variables.h"
#include <stdlib.h>

void update_scene(void)
{
    scenes[current_scene].update();
    frame_count++;
}

void next_scene(void)
{
    change_scene(current_scene + 1);
}

void change_scene(uint8_t next_scene)
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

void wait_for_video(void)
{
    SMS_waitForVBlank();
    SMS_copySpritestoSAT();
}

void wait_for_frame(void)
{
    // if (PSGGetStatus() == PSG_PLAYING)
    // {
    //     SMS_mapROMBank(current_music_bank);
    //     wait_for_audio();
    // }

    SMS_mapROMBank(current_gfx_bank);
    wait_for_video();
}
