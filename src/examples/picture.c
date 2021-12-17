#include "picture.h"
#include "../assets2banks.h" // Generated with the assets task
#include "../libs/SMSlib.h"

unsigned int scroll_x;

void init_picture(void)
{
    SMS_loadPSGaidencompressedTiles(test_tiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(0, 0, test_tilemap_stmcompr);
    SMS_loadBGPalette(test_palette_bin);

    SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK); // Hide stuff for scrolling

    scroll_x = 0;
}

void animate_picture(void)
{
    SMS_setBGScrollX(scroll_x++ >> 3);
}
