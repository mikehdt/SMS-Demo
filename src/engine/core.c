#include "core.h"
#include "../assets2banks.h"
#include "../libs/SMSlib.h"

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

void wait_for_vblank(void)
{
    SMS_waitForVBlank();
    SMS_copySpritestoSAT(); // Update any sprite shenanigans
}

void clear_tilemap(uint16_t tile) // Must be 16-bit, not 8-bit, or else sad VDP
{
    // From sverx, a more efficient method
    SMS_VRAMmemsetW(XYtoADDR(0, 0), tile, SCREEN_ROWS * SCREEN_COLUMNS * 2);
}
