#include "scroller.h"
#include "../assets2banks.h" // Generated with the assets task
#include "../libs/SMSlib.h"
#include <stdbool.h>

unsigned int scroll_x[9];
unsigned char lineCnt;

void load_assets(void)
{
    // SMS_mapROMBank(test_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(sunset_tiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(0, 0, sunset_tilemap_stmcompr);
    SMS_loadBGPalette(sunset_palette_bin);
}

void scrollInterruptHandler(void)
{
    SMS_setBGScrollX(scroll_x[++lineCnt] >> 2);
}

void enable_scrolling(void)
{
    SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK);
    SMS_setLineInterruptHandler(&scrollInterruptHandler);
    SMS_setLineCounter(24); // Every 25 scanlines
    SMS_enableLineInterrupt();
    SMS_setBGScrollX(0);

    scroll_x[0] = 0xFFFF;
    scroll_x[1] = 0xFFFF;
    scroll_x[2] = 0xFFFF;
    scroll_x[3] = 0xFFFF;
    scroll_x[4] = 0xFFFF;
    scroll_x[5] = 0xFFFF;
    scroll_x[6] = 0xFFFF;
    scroll_x[7] = 0xFFFF;
    scroll_x[8] = 0xFFFF;
    lineCnt = 0;
}

void init_background(void)
{
    load_assets();
    enable_scrolling();
}

void animate_background(void)
{
    SMS_setBGScrollX(scroll_x[0] >> 2);
    scroll_x[0] -= 9;
    scroll_x[1] -= 8;
    scroll_x[2] -= 7;
    scroll_x[3] -= 6;
    scroll_x[4] -= 5;
    scroll_x[5] -= 4;
    scroll_x[6] -= 3;
    scroll_x[7] -= 2;
    scroll_x[8] -= 1;

    lineCnt = 0;
}

void init_sprites(void)
{
}

void animate_sprites(void)
{
}
