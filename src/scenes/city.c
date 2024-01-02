#include "city.h"
#include "../assets2banks.h"
#include "../engine/global_constants.h"
#include "../engine/global_helpers.h"
#include "../engine/global_variables.h"
#include "../engine/palettes.h"
#include "../engine/sprites.h"
#include "../helpers/scroll_interrupt.h"
#include "../libs/SMSlib.h"
#include <stdint.h>

#define SCENE_OFFSET 257

uint16_t count;

unsigned char cityLineCnt = 0;
uint16_t next_scroll_value;
uint16_t city_scroll_x[4];

void cityScrollHandler(void)
{
    INLINE_SMS_setBGScrollX(next_scroll_value);

    if (++cityLineCnt > 3)
        cityLineCnt = 3;

    next_scroll_value = city_scroll_x[cityLineCnt] >> 4;
}

void update_scroll_pos(void)
{
    cityLineCnt = 0;
    city_scroll_x[0] += 4;
    city_scroll_x[1] += 4;
    city_scroll_x[2] += 2;
    city_scroll_x[3] += 1;
    next_scroll_value = city_scroll_x[0] >> 4;
}

void city_init(void)
{
    city_scroll_x[0] = 0xFFFF;
    city_scroll_x[1] = 0xFFFF;
    city_scroll_x[2] = 0xFFFF;
    city_scroll_x[3] = 0xFFFF;
    next_scroll_value = 0xFFFF;

    SMS_displayOff();

    wait_for_frame();
    load_palette(palette_black, PALETTE_BACKGROUND);

    SMS_mapROMBank(cityscape_palette_bin_bank);
    SMS_loadPSGaidencompressedTiles(cityscape_tiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(0, 0, cityscape_tilemap_stmcompr);

    set_scroll(15, &cityScrollHandler); // Seems to be off by 1px vertically?

    SMS_displayOn();

    wait_for_frame();
    update_scroll_pos();

    for (unsigned char i = 0; i < 10; i++)
    {
        fade_from_white(cityscape_palette_bin, i);

        wait_for_frame();
        update_scroll_pos();
        wait_for_frame();
        update_scroll_pos();
        wait_for_frame();
        update_scroll_pos();
    }
}

void city_update(void)
{
    wait_for_frame();
    update_scroll_pos();
}

void city_end(void)
{
    for (int i = 0; i < 10; i++)
    {
        fade_to_black(cityscape_palette_bin, i);

        wait_for_frame();
        update_scroll_pos();
        wait_for_frame();
        update_scroll_pos();
        wait_for_frame();
        update_scroll_pos();
    }

    clear_scroll();

    SMS_displayOff();

    wait_for_frame();
    clear_sprites();

    SMS_useFirstHalfTilesforSprites(false);
    SMS_displayOn();
}
