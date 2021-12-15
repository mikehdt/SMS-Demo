#include <stdbool.h>
#include "libs/SMSlib.h"
#include "examples/picture.h"

// Some code unceremoniously borrowed from the excellent Gotris project
#define SCREEN_ROWS 24
#define SCREEN_COLUMNS 32

void init_console(void)
{
    // SMS_init(); // Unneeded because of crt0?
    // SMS_setSpriteMode(SPRITEMODE_NORMAL);  // Not sure what this is for?
    SMS_useFirstHalfTilesforSprites(true); // Seems to clear the tiles?
    SMS_displayOn();
}

void clear_tilemap(void)
{
    unsigned char i, j;

    SMS_setNextTileatXY(0, 0);

    for (j = 0; j < SCREEN_ROWS; j++)
        for (i = 0; i < SCREEN_COLUMNS; i++)
            SMS_setTile(0);
}

void main(void)
{
    int testVar = 0;

    // Common initalisation
    init_console();
    clear_tilemap();

    // Silly-project specific
    init_picture();

    while (true)
    {
        // This is just to test local variable debugging
        if (++testVar >= 100)
            testVar = 0;

        SMS_waitForVBlank();
    }
}

// Stop VScode from fussing about these function calls
#ifndef __INTELLISENSE__
SMS_EMBED_SEGA_ROM_HEADER(9999, 0);
SMS_EMBED_SDSC_HEADER_AUTO_DATE(1, 0, "Mike Hopkins", "Hello World", "I have no idea what I'm doing");
#endif
