#include "../assets2banks.h"
#include "../engine/scenes.h"
#include "../engine/tilemap.h"
#include "../libs/SMSlib.h"

void logo_init(void)
{
    SMS_mapROMBank(da_mini_palette_bin_bank);
    SMS_loadPSGaidencompressedTiles(da_mini_tiles_psgcompr, 1);
    SMS_loadBGPalette(da_mini_palette_bin);

    SMS_loadSTMcompressedTileMap(11, 12, da_mini_tilemap_stmcompr);

    // Hacky!
    // if (current_music_bank == 0)
    //     play_song();
}

void logo_update(void)
{
    wait_for_frame();
    // SMS_copySpritestoSAT();
}

void logo_end(void) {}
