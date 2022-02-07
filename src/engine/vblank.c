#include "../libs/SMSlib.h"
#include "vblank.h"

void wait_for_vblank(void)
{
    SMS_waitForVBlank();
    SMS_copySpritestoSAT(); // Update any sprite shenanigans
}
