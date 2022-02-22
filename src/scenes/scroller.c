#include "scroller.h"
#include "../assets2banks.h" // Generated with the assets task
#include "../libs/SMSlib.h"
#include <stdbool.h>
#include <stdint.h>

uint16_t pic_scroll_x[11];
unsigned char lineCnt;

void load_assets(void)
{
    SMS_mapROMBank(sunset_tiles_psgcompr_bank);

    SMS_loadPSGaidencompressedTiles(sunset_tiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(0, 0, sunset_tilemap_stmcompr);
    SMS_loadBGPalette(sunset_palette_bin);
}

void scrollInterruptHandler(void)
{
    SMS_setBGScrollX(pic_scroll_x[++lineCnt] >> 2);
}

void enable_scrolling(void)
{
    SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK);
    SMS_setLineInterruptHandler(&scrollInterruptHandler);
    SMS_setLineCounter(24); // Every 25 scanlines
    SMS_enableLineInterrupt();
    SMS_setBGScrollX(0);

    pic_scroll_x[0] = 0xFFFF;
    pic_scroll_x[1] = 0xFFFF;
    pic_scroll_x[2] = 0xFFFF;
    pic_scroll_x[3] = 0xFFFF;
    pic_scroll_x[4] = 0xFFFF;
    pic_scroll_x[5] = 0xFFFF;
    pic_scroll_x[6] = 0xFFFF;
    pic_scroll_x[7] = 0xFFFF;
    pic_scroll_x[8] = 0xFFFF;
    pic_scroll_x[9] = 0xFFFF;
    pic_scroll_x[10] = 0xFFFF;
    lineCnt = 0;
}

void scroller_scene_init(void)
{
    SMS_initSprites(); // For some reason there's corruption after plasma
    load_assets();
    enable_scrolling();
}

void scroller_scene_update(void)
{
    SMS_waitForVBlank();

    SMS_setBGScrollX(pic_scroll_x[0] >> 2);

    pic_scroll_x[0] -= 9;
    pic_scroll_x[1] -= 9;
    pic_scroll_x[2] -= 8;
    pic_scroll_x[3] -= 7;
    pic_scroll_x[4] -= 6;
    pic_scroll_x[5] -= 5;
    pic_scroll_x[6] -= 4;
    pic_scroll_x[7] -= 3;
    pic_scroll_x[8] -= 2;
    pic_scroll_x[9] -= 1;
    pic_scroll_x[10] -= 1;

    lineCnt = 0;
}

// also disable int handling
void scroller_scene_end(void)
{
    SMS_VDPturnOffFeature(VDPFEATURE_LEFTCOLBLANK);
    SMS_disableLineInterrupt();
    SMS_setBGScrollX(0);
}
