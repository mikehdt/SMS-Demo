#include "city.h"
#include "../assets2banks.h"
#include "../engine/global_constants.h"
#include "../engine/global_helpers.h"
#include "../engine/palettes.h"
#include "../engine/scenes.h"
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

    if (++cityLineCnt == 3)
        SMS_setLineCounter(127); // Every n + 1 scanlines (0 indexed)

    next_scroll_value = city_scroll_x[cityLineCnt] >> 5;
}

void update_scroll_pos(void)
{
    cityLineCnt = 0;
    // Position 0 is not used, it's sacrificial
    city_scroll_x[1] += 3;
    city_scroll_x[2] += 2;
    city_scroll_x[3] += 1;
    next_scroll_value = city_scroll_x[1] >> 5;
}

void city_init(void)
{
    current_stage = 1;

    city_scroll_x[0] = 0xFFFF;
    city_scroll_x[1] = 0xFFFF;
    city_scroll_x[2] = 0xFFFF;
    city_scroll_x[3] = 0xFFFF;
    next_scroll_value = 0xFFFF;

    wait_for_frame();
    load_palette(palette_black, PALETTE_BACKGROUND);

    SMS_mapROMBank(cityscape_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(cityscape_tiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(0, 0, cityscape_tilemap_stmcompr);

    set_scroll(15, &cityScrollHandler);
    update_scroll_pos();
}

void city_scroll(void)
{
    wait_for_frame();
    SMS_setLineCounter(15); // Reset
    update_scroll_pos();
}

void city_update(void)
{
    if (current_stage == 1)
    {
        for (unsigned char i = 0; i < 10; i++)
        {
            fade_from_white(cityscape_palette_bin, i);

            city_scroll();
            city_scroll();
            city_scroll();
        }
    }
    else
    {
        city_scroll();
    }
}

void city_end(void)
{
    for (int i = 0; i < 10; i++)
    {
        fade_to_black(cityscape_palette_bin, i);

        city_update();
        city_update();
        city_update();
    }

    clear_scroll();

    SMS_displayOff();

    wait_for_frame();
    clear_sprites();

    SMS_useFirstHalfTilesforSprites(false);
    SMS_displayOn();
}
