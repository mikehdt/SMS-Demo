#include <stdbool.h>
#include "../libs/SMSlib.h"
#include "assets2banks.h" // Generated with the assets task

// A fair bit of code unceremoniously borrowed from the excellent Gotris project
#define SCREEN_ROWS 24
#define SCREEN_COLUMNS 32

void clear_tilemap()
{
    unsigned char i, j;
    SMS_setNextTileatXY(0, 0);
    for (j = 0; j < SCREEN_ROWS; j++)
    {
        for (i = 0; i < SCREEN_COLUMNS; i++)
        {
            SMS_setTile(0);
        }
    }
}

void init_console(void)
{
    // SMS_init(); // Unneeded because of crt0?
    // SMS_setSpriteMode(SPRITEMODE_NORMAL);  // ?
    SMS_useFirstHalfTilesforSprites(true); // ?
    SMS_displayOn();
}

void load_test_assets(void)
{
    // SMS_mapROMBank(test_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(test_tiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(0, 0, test_tilemap_stmcompr);
    SMS_loadBGPalette(test_palette_bin);
}

void main(void)
{
    int testVar;

    init_console();
    clear_tilemap();
    load_test_assets();

    testVar = 0;

    while (true)
    {
        // This is just to test local variable debugging
        if (++testVar >= 100)
            testVar = 0;

        SMS_waitForVBlank();
    }
}

SMS_EMBED_SEGA_ROM_HEADER(9999, 0);
SMS_EMBED_SDSC_HEADER_AUTO_DATE(1, 0, "Mike Hopkins", "Hello World", "I have no idea what I'm doing");
