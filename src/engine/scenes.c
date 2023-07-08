#include "scenes.h"
#include "../libs/PSGlib.h"
#include "../libs/SMSlib.h"
#include "../scenes/config_scenes.h"
#include "audio.h"
#include "global_variables.h"
#include <stdlib.h>

void scene_update(void)
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

        frame_count = 0;
        current_scene = target_scene;

        if (target_scene_stage != 0)
        {
            current_scene_stage = target_scene_stage;
            target_scene_stage = 0;
        }

        scenes[current_scene].init();
    }
}

void next_scene(void)
{
    uint8_t next_scene;

    next_scene = current_scene + 1;

    // Throws some weird SDCC warning, I mean seriously what
    // if (next_scene >= MAX_SCENES)
    //     next_scene == 0;

    transition_to_scene(next_scene);
}

void set_next_scene_stage(uint8_t target_stage)
{
    target_scene_stage = target_stage;
}

void wait_for_video(void)
{
    SMS_waitForVBlank();
    SMS_copySpritestoSAT();
}

void wait_for_frame(void)
{
    if (PSGGetStatus() == PSG_PLAYING)
        wait_for_audio(current_music_bank);

    if (PSGSFXGetStatus() == PSG_PLAYING)
        wait_for_audio(current_fx_bank);

    SMS_mapROMBank(current_rom_bank);

    wait_for_video();
}
