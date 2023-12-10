#include "console_init.h"
#include "../libs/SMSlib.h"
#include "global_variables.h"
#include "palettes.h"
#include "sprites.h"
#include "tilemap.h"
#include <stdbool.h>

void console_init(void)
{
    current_scene = 0;

    // SMS_VDPturnOnFeature(VDPFEATURE_EXTRAHEIGHT); // PAL / SMS II only
    // SMS_VDPturnOnFeature(VDPFEATURE_240LINES);    // PAL / SMS II only

    SMS_setSpriteMode(SPRITEMODE_NORMAL);

    set_palette(palette_black, PALETTE_BOTH);
    load_blank_tile(0);
    clear_tilemap(0);

    SMS_displayOn();
}
