#include "scenes.h"
#include "../libs/PSGlib.h"
#include "../libs/SMSlib.h"
#include "../scenes/_scenes.h"
#include "global_variables.h"
#include <stdlib.h>

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

void waitForAudio(uint8_t audio_bank)
{
    SMS_mapROMBank(audio_bank);

    // Volume fade
    if (target_volume < current_volume)
    {
        current_volume = current_volume - 4;
        PSGSetMusicVolumeAttenuation(current_volume >> 4);
    }
    else if (target_volume > current_volume)
    {
        current_volume = current_volume + 4;
        PSGSetMusicVolumeAttenuation(current_volume >> 4);
    }

    PSGFrame();
}

void waitForVideo(void)
{
    SMS_waitForVBlank();
    SMS_copySpritestoSAT();
}

void waitForFrame(void)
{
    if (PSGGetStatus() == PSG_PLAYING)
        waitForAudio(current_music_bank);

    if (PSGSFXGetStatus() == PSG_PLAYING)
        waitForAudio(current_fx_bank);

    SMS_mapROMBank(current_rom_bank);

    waitForVideo();
}
