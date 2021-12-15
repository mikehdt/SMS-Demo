#include "picture.h"
#include "assets2banks.h" // Generated with the assets task
#include "../libs/SMSlib.h"

void init_picture()
{
    SMS_loadPSGaidencompressedTiles(test_tiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(0, 0, test_tilemap_stmcompr);
    SMS_loadBGPalette(test_palette_bin);
}
