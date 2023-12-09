#include "../assets2banks.h"
// #include "../engine/global_variables.h"
// #include "../engine/scenes.h"
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
    // if (frame_count == 24)
    // {
    // }
    // else if (frame_count == 192)
    // {
    //     clear_tilemap(0);
    // }

    // wait_for_frame();

    // if (frame_count == 320)
    // {
    //     next_scene();
    // }

    SMS_waitForVBlank();
    // SMS_copySpritestoSAT();
}

void logo_end(void) {}
