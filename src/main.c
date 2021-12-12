#include "..\lib\SMSlib.h"
#include "banks\bank2.h"

#define SPLASH_TILES 0

void hello_world()
{
    SMS_loadTiles(test_tiles_bin, SPLASH_TILES, 8);
    SMS_loadTileMap(0, 0, test_tilemap_bin, 8);
    SMS_loadBGPalette(test_palette_bin);
}

void main(void)
{
    SMS_mapROMBank(2);
    hello_world();
    SMS_displayOn();
    for (;;)
    {
        SMS_waitForVBlank();
    }
}

SMS_EMBED_SEGA_ROM_HEADER(9999, 0);
SMS_EMBED_SDSC_HEADER(1, 0, 2021, 12, 12, "Mike", "Hello World", "I have no idea what I'm doing");
