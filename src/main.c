// Need to also set the correct REL linking in build.bat for now...
#include "examples/picture.h"
// #include "examples/scroller.h"
// #include "examples/sphere.h"
// #include "examples/grid.h"
#include "libs/SMSlib.h"
#include "utils.h"
#include <stdbool.h>

void init_console(void)
{
    // SMS_VDPturnOnFeature(VDPFEATURE_EXTRAHEIGHT); // PAL / SMS II only
    // SMS_VDPturnOnFeature(VDPFEATURE_240LINES);    // PAL / SMS II only
    SMS_setSpriteMode(SPRITEMODE_NORMAL);  // Set this to the expected format
    SMS_useFirstHalfTilesforSprites(true); // Are sprite memory reads limited?
    SMS_displayOn();
}

void main(void)
{
    // Common initalisation
    init_console();
    clear_tilemap(0);

    // Project specific
    init_background();
    init_sprites();

    while (true)
    {
        animate_background();
        animate_sprites();

        wait_for_frame();
    }
}

// Stop VScode from fussing about these function calls
#ifndef __INTELLISENSE__
SMS_EMBED_SEGA_ROM_HEADER(9999, 0);
SMS_EMBED_SDSC_HEADER_AUTO_DATE(1, 0, "Mike Hopkins", "Hello World",
                                "I have no idea what I'm doing");
#endif
