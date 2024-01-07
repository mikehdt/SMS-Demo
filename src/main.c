#include "config_scenes.h"
#include "engine/console_init.h"
#include "engine/scenes.h"
#include "libs/SMSlib.h"
#include <stdbool.h>
#include <stdint.h>

#define DEBUG 1

void main(void)
{
    // The pause and reset buttons are given over to our code to handle however
    // we see fit. From what I understand, the pause button triggers an
    // interrupt, but reset is detected via a bitmask of keys currently pressed.
    while (true)
    {
        console_init();
        scenes_init();
        jump_to_scene(DEFAULT);

        do
        {
            update_scene();

            // This is fine if it's performant; less responsive if under CPU stress
            if (DEBUG && (SMS_getKeysReleased() & PORT_A_KEY_1))
                next_scene();
        } while (~(SMS_getKeysPressed() & RESET_KEY));
    }
}

// Stop VScode from fussing about these function calls
#ifndef __INTELLISENSE__
SMS_EMBED_SEGA_ROM_HEADER(9999, 0);
SMS_EMBED_SDSC_HEADER_AUTO_DATE(1, 0, "disasterarea", "invasion",
                                "A demo for the SMS ][");
#endif
