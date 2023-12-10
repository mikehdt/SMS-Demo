#include "audio.h"
#include "../assets2banks.h"
#include "../libs/PSGlib.h"
#include "../libs/SMSlib.h"
#include "global_variables.h"

void map_audio_bank(void)
{
    if (SMS_getROMBank() != madness_psg_bank)
        SMS_mapROMBank(madness_psg_bank);
}

void update_audio(void)
{
    // Volume fade
    // if (target_attenuation < current_attenuation)
    // {
    //     current_attenuation = current_attenuation - 4;
    //     PSGSetMusicVolumeAttenuation(current_attenuation >> 4);
    // }
    // else if (target_attenuation > current_attenuation)
    // {
    //     current_attenuation = current_attenuation + 4;
    //     PSGSetMusicVolumeAttenuation(current_attenuation >> 4);
    // }

    if (PSGGetStatus() == PSG_PLAYING)
    {
        map_audio_bank();
        PSGFrame();
    }
}

void play_song(void)
{
    map_audio_bank();
    PSGPlay(madness_psg);
}
