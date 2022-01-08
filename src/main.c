// Need to also set the correct REL linking in build.bat for now...
#include "scenes/picture.h"
// #include "scenes/scroller.h"
// #include "scenes/sphere.h"
// #include "scenes/grid.h"
#include "engine/core.h"
#include "libs/SMSlib.h"
#include <stdbool.h>

void main(void)
{
    // Common initalisation
    init_console();
    clear_tilemap(0);

    // Project specific
    init_sprites();
    init_background();

    while (true)
    {
        animate_sprites();
        animate_background();

        wait_for_frame();
    }
}

// Stop VScode from fussing about these function calls
#ifndef __INTELLISENSE__
SMS_EMBED_SEGA_ROM_HEADER(9999, 0);
SMS_EMBED_SDSC_HEADER_AUTO_DATE(1, 0, "Mike Hopkins", "Hello World",
                                "I have no idea what I'm doing");
#endif
