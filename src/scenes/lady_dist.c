#include "../assets2banks.h"
#include "../engine/palettes.h"
#include "../engine/scenes.h"
#include "../engine/tilemap.h"
#include "../helpers/scroll_interrupt.h"
#include "../libs/SMSlib.h"
#include "lady_dist.h"

void lady_dist_init(void)
{
    SMS_displayOff();
    SMS_waitForVBlank();
    SMS_mapROMBank(lady_palette_bin_bank);
    SMS_loadBGPalette(lady_palette_bin);
    SMS_loadSpritePalette(lady_palette_bin);
    SMS_loadPSGaidencompressedTiles(lady_tiles_psgcompr, 0);
    SMS_loadPSGaidencompressedTiles(lady_dist_tiles_psgcompr, 256);

    clear_tilemap(0);

    SMS_loadSTMcompressedTileMap(7, 0, lady_dist_tilemap_stmcompr);
    SMS_displayOn();
}

void lady_dist_update(void)
{
    SMS_waitForVBlank();
    SMS_waitForVBlank();

    SMS_setBGScrollX(cur_frame);

    if (cur_frame < 60)
    {
        SMS_setBGScrollX(cur_frame);
    }
    else if (cur_frame == 60)
    {
        SMS_setBGScrollX(cur_frame - 60);
        SMS_loadSTMcompressedTileMap(6, 0, lady_tilemap_stmcompr);
    }
    else if (cur_frame < 120)
    {
        SMS_setBGScrollX(cur_frame - 90);
    }
    else if (cur_frame == 120)
    {
        cur_stage = 3;
        next_scene();
    }

    cur_frame++;
}

void lady_dist_end(void)
{
    SMS_waitForVBlank();

    clear_scroll();
}
