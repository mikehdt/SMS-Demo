#include "default.h"
#include "../assets2banks.h"
#include "../config_scenes.h"
#include "../engine/palettes.h"
#include "../engine/scenes.h"
#include "../engine/tilemap.h"

#define PSGLIB_MULTIBANK 1
#include "../libs/PSGlib.h"
#include "../libs/SMSlib.h"

void psgHandler(void)
{
    SMS_saveROMBank();
    PSGFrame();
    SMS_restoreROMBank();
}

void default_init(void)
{
    // Hook to play the PSG frame even if the CPU is held up doing other stuff
    SMS_setFrameInterruptHandler(&psgHandler);
    PSGPlayNoRepeat(test_ct2_psg, test_ct2_psg_bank);

    load_palette(palette_black, PALETTE_BACKGROUND);
    clear_tilemap(0);
    clear_extra_tilemap(0);

    next_scene();
}
