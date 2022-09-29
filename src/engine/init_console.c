#include "init_console.h"
#include "../engine/palettes.h"
#include "../libs/SMSlib.h"
#include "clear_tilemap.h"
#include <stdbool.h>

void init_console(void)
{
    // SMS_VDPturnOnFeature(VDPFEATURE_EXTRAHEIGHT); // PAL / SMS II only
    // SMS_VDPturnOnFeature(VDPFEATURE_240LINES);    // PAL / SMS II only
    SMS_initSprites();
    SMS_setSpriteMode(SPRITEMODE_NORMAL);
    SMS_useFirstHalfTilesforSprites(true);

    load_blank_tile(0);
    set_palette(palette_black, PALETTE_BACKGROUND);
    clear_tilemap(0);

    SMS_displayOn();
}
