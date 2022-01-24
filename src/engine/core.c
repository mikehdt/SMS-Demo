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
    // SMS_loadPSGaidencompressedTiles(blank_tiles_psgcompr, 0);
    // SMS_loadBGPalette();
    // SMS_loadSpritePalette();

    // Should probably wipe the tile library as well?
    clear_tilemap(0);

    SMS_displayOn();
}

void wait_for_frame(void)
{
    SMS_waitForVBlank();
    SMS_copySpritestoSAT(); // Update any sprite shenanigans
}

void clear_tilemap(unsigned int tile) // Must be an int, not a uint_8t or such
{
    // From sverx, a more efficient method
    SMS_VRAMmemsetW(XYtoADDR(0, 0), tile, SCREEN_ROWS * SCREEN_COLUMNS * 2);
}
