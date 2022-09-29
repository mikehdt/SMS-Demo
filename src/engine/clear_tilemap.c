#include "clear_tilemap.h"
#include "../assets2banks.h" // Generated with the assets task
#include "../engine/globals.h"
#include "../libs/SMSlib.h"

void load_blank_tile(uint16_t tile)
{
    // Blank tile
    SMS_mapROMBank(blank_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(blank_tiles_psgcompr, 0);
}

void clear_tilemap(uint16_t tile) // Must be 16-bit, or else sad VDP
{
    // From sverx, a more efficient method
    SMS_VRAMmemsetW(XYtoADDR(0, 0), tile, (SCREEN_ROWS * SCREEN_COLUMNS * 2));
}
