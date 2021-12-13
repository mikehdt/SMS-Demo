#include <stdbool.h>
#include "../libs/SMSlib.h"
#include "assets2banks.h" // Generated with the assets task

unsigned char current_resource_bank;

void init_console(void)
{
    // SMS_init(); // Unneeded because of crt0?
    SMS_displayOn();
}

void load_test_assets(void)
{
    SMS_mapROMBank(test_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(test_tiles_psgcompr, 0);
    SMS_loadTileMap(0, 0, test_tilemap_bin, test_tilemap_bin_size);
}

void update_state(void)
{
    SMS_waitForVBlank();
}

void main(void)
{
    init_console();
    load_test_assets();

    while (true)
    {
        update_state();
    }
}

SMS_EMBED_SEGA_ROM_HEADER(9999, 0);
SMS_EMBED_SDSC_HEADER_AUTO_DATE(1, 0, "Mike Hopkins", "Hello World", "I have no idea what I'm doing");
