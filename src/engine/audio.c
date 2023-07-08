#include "audio.h"
#include "../assets2banks.h"
#include "../libs/PSGlib.h"
#include "../libs/SMSlib.h"
#include "global_variables.h"

void wait_for_audio(uint8_t audio_bank)
{
    SMS_mapROMBank(audio_bank);

    // Volume fade
    if (target_attenuation < current_attenuation)
    {
        current_attenuation = current_attenuation - 4;
        PSGSetMusicVolumeAttenuation(current_attenuation >> 4);
    }
    else if (target_attenuation > current_attenuation)
    {
        current_attenuation = current_attenuation + 4;
        PSGSetMusicVolumeAttenuation(current_attenuation >> 4);
    }

    PSGFrame();
}

void play_song(void)
{
    SMS_mapROMBank(madness_psg_bank);
    current_music_bank = madness_psg_bank;
    PSGPlay(madness_psg);
}
