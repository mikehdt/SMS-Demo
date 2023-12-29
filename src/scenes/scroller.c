#include "scroller.h"
#include "../assets2banks.h"
#include "../engine/global_helpers.h"
#include "../engine/tilemap.h"
#include "../libs/SMSlib.h"
#include <stdbool.h>
#include <stdint.h>

uint16_t pic_scroll_x[11];
unsigned char lineCnt;

void scrollInterruptHandler(void)
{
    SMS_setBGScrollX(pic_scroll_x[lineCnt++] >> 2);
}

void init_scrolling(void)
{
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

void scroller_init(void)
{
    init_scrolling();

    SMS_displayOff();

    wait_for_frame();

    SMS_mapROMBank(sunset_palette_bin_bank);
    SMS_loadPSGaidencompressedTiles(sunset_tiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(0, 0, sunset_tilemap_stmcompr);
    SMS_loadBGPalette(sunset_palette_bin);

    SMS_displayOn();
}

void scroller_update(void)
{
    wait_for_frame();

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
void scroller_end(void)
{
    wait_for_frame();

    SMS_displayOff();

    load_blank_tile(0);
    clear_tilemap(0);

    wait_for_frame();

    SMS_displayOn();
}
