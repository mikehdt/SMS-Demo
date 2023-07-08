#include "engine/console_init.h"
#include "engine/keys.h"
#include "engine/scenes.h"
#include "libs/SMSlib.h"
#include "scenes/config_scenes.h"
#include <stdbool.h>
#include <stdint.h>

void main(void)
{
    // The pause and reset buttons are given over to our code to handle however
    // we see fit. From what I understand, the pause button triggers an
    // interrupt, but reset is detected via a bitmask of keys currently pressed.
    uint16_t keys_pressed;
    // static bool global_pause;

    while (true)
    {
        // Common initalisation
        console_init();
        scenes_init();

        // Loop whilst the reset key is NOT pressed
        do
        {
            keys_pressed = SMS_getKeysPressed();

            // Maybe add back if feeling fancy
            // if (SMS_queryPauseRequested())
            // {
            //     SMS_resetPauseRequest();
            //     global_pause = !global_pause;

            //     if (global_pause)
            //         continue;
            // }

            // Enable for debugging :)
            // check_keys();
            scene_update();
        } while (~(keys_pressed & RESET_KEY));
    }
}

// Stop VScode from fussing about these function calls
#ifndef __INTELLISENSE__
SMS_EMBED_SEGA_ROM_HEADER(9999, 0);
SMS_EMBED_SDSC_HEADER_AUTO_DATE(1, 0, "Mike Hopkins", "SMS Demo",
                                "Mucking about with the Master System");
#endif
