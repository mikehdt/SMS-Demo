#include "init_console.h"
#include "../helpers/clear_tilemap.h"
#include "../libs/SMSlib.h"
#include <stdbool.h>

void init_console(void)
{
    // SMS_VDPturnOnFeature(VDPFEATURE_EXTRAHEIGHT); // PAL / SMS II only
    // SMS_VDPturnOnFeature(VDPFEATURE_240LINES);    // PAL / SMS II only
    SMS_initSprites();
    SMS_setSpriteMode(SPRITEMODE_NORMAL);  // Set this to the expected format
    SMS_useFirstHalfTilesforSprites(true); // Are sprite memory reads limited?

    // Should probably wipe the tile library as well?
    clear_tilemap(0);

    SMS_displayOn();
}
