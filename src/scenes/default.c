#include "default.h"
#include "../assets2banks.h"
#include "../config_scenes.h"
#include "../engine/global_helpers.h"
#include "../engine/scenes.h"

#define PSGLIB_MULTIBANK 1
#include "../libs/PSGlib.h"
#include "../libs/SMSlib.h"

void psgHandler(void)
{
    // if (PSGGetStatus() == PSG_PLAYING)
    // {
    SMS_saveROMBank();
    PSGFrame();
    SMS_restoreROMBank();
    // }
}

void default_update(void)
{
    SMS_setFrameInterruptHandler(&psgHandler);

    PSGPlay(test_ct2_psg, test_ct2_psg_bank);

    next_scene();
}
