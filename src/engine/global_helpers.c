#include "../assets2banks.h"
#include "../libs/PSGlib.h"
#include "../libs/SMSlib.h"

void wait_for_frame(void)
{
    if (PSGGetStatus() == PSG_PLAYING)
    {
        SMS_saveROMBank();
        PSGFrame();
        SMS_restoreROMBank();
    }

    SMS_waitForVBlank();
}
