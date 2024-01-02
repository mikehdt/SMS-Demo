#include "default.h"
#include "../assets2banks.h"
#include "../config_scenes.h"
#include "../engine/global_helpers.h"
#include "../engine/scenes.h"

#define PSGLIB_MULTIBANK 1
#include "../libs/PSGlib.h"

void default_update(void)
{
    PSGPlay(test_ct2_psg, test_ct2_psg_bank);
    next_scene();
}
