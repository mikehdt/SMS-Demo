#include "grid.h"
#include "../assets2banks.h" // Generated with the assets task
#include "../libs/SMSlib.h"
#include <stdint.h>
#include <stdlib.h>

uint8_t show_mesh = 0;

void init_background(void)
{
    // SMS_loadPSGaidencompressedTiles(mesh_01_tiles_psgcompr, 0);
    // SMS_loadPSGaidencompressedTiles(mesh_02_tiles_psgcompr, 7);
    // SMS_loadPSGaidencompressedTiles(mesh_03_tiles_psgcompr, 66);
    // SMS_loadPSGaidencompressedTiles(mesh_04_tiles_psgcompr, 97);
    // SMS_loadPSGaidencompressedTiles(mesh_05_tiles_psgcompr, 163);
    // SMS_loadPSGaidencompressedTiles(mesh_06_tiles_psgcompr, 180);
    // SMS_loadPSGaidencompressedTiles(mesh_07_tiles_psgcompr, 297);
    // SMS_loadPSGaidencompressedTiles(mesh_08_tiles_psgcompr, 334);
    // SMS_loadPSGaidencompressedTiles(mesh_09_tiles_psgcompr, 422);
    // SMS_loadSTMcompressedTileMap(12, 7, mesh_09_tilemap_stmcompr);
    // SMS_loadBGPalette(mesh_01_palette_bin);
}

void animate_background(void)
{
    return;

    // This is a mess. Needs a re-think...
    // switch (show_mesh >> 3)
    // {
    //     case 0:
    //         SMS_loadSTMcompressedTileMap(12, 7, mesh_01_tilemap_stmcompr);
    //         break;

    //     case 1:
    //         SMS_loadSTMcompressedTileMap(12, 7, mesh_02_tilemap_stmcompr);
    //         break;

    //     case 2:
    //         SMS_loadSTMcompressedTileMap(11, 7, mesh_03_tilemap_stmcompr);
    //         break;

    //     case 3:
    //         SMS_loadSTMcompressedTileMap(11, 7, mesh_04_tilemap_stmcompr);
    //         break;

    //     case 4:
    //         SMS_loadSTMcompressedTileMap(11, 6, mesh_05_tilemap_stmcompr);
    //         break;

    //     case 5:
    //         SMS_loadSTMcompressedTileMap(11, 6, mesh_06_tilemap_stmcompr);
    //         break;

    //     case 6:
    //         SMS_loadSTMcompressedTileMap(10, 6, mesh_07_tilemap_stmcompr);
    //         break;

    //     case 7:
    //         SMS_loadSTMcompressedTileMap(10, 5, mesh_08_tilemap_stmcompr);
    //         break;

    //     case 8:
    //         SMS_loadSTMcompressedTileMap(10, 5, mesh_09_tilemap_stmcompr);
    //         break;
    // }

    // if (show_mesh++ > 8 * 3)
    //     show_mesh = 0;
}

void init_sprites(void)
{
}

void animate_sprites(void)
{
}
