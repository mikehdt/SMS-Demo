#include "../assets2banks.h"
#include "../libs/PSGlib.h"
#include "../libs/SMSlib.h"

void start_song(void)
{
    SMS_mapROMBank(madness_psg_bank);
    PSGPlay(madness_psg);
}

void wait_for_frame(void)
{
    if (PSGGetStatus() == PSG_PLAYING)
    {
        if (SMS_getROMBank() != madness_psg_bank)
            SMS_mapROMBank(madness_psg_bank);

        PSGFrame();
    }

    SMS_waitForVBlank();
}
