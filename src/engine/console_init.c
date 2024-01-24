#include "../libs/SMSlib.h"
#include "console_init.h"
#include "palettes.h"
#include "sprites.h"
#include "tilemap.h"
#include <stdbool.h>

void console_init(void)
{
    // Some of these are already default; Reset them in case of skip during dev
    SMS_displayOff();
    SMS_setSpriteMode(SPRITEMODE_NORMAL);
    SMS_disableLineInterrupt();
    SMS_setBGScrollX(0);
    SMS_setBGScrollY(0);
    // SMS_VDPturnOnFeature(VDPFEATURE_EXTRAHEIGHT); // PAL / SMS II only
    // SMS_VDPturnOnFeature(VDPFEATURE_240LINES);    // PAL / SMS II only

    load_palette(palette_black, PALETTE_BOTH);
    load_blank_tile(0);
    clear_tilemap(0);

    SMS_displayOn();
    SMS_waitForVBlank();
}
