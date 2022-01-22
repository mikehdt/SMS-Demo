#include "grid.h"
#include "../assets2banks.h" // Generated with the assets task
#include "../libs/SMSlib.h"
#include <stdint.h>
#include <stdlib.h>

uint8_t show_mesh = 0;

void grid_scene_init(void)
{
    SMS_loadBGPalette(mesh_01_palette_bin);
}

void grid_scene_update(void)
{
    switch (show_mesh >> 3)
    {
        case 0:
            SMS_loadPSGaidencompressedTiles(mesh_01_tiles_psgcompr, 0);
            SMS_loadSTMcompressedTileMap(0, 0, mesh_01_tilemap_stmcompr);
            break;

        case 1:
            SMS_loadPSGaidencompressedTiles(mesh_02_tiles_psgcompr, 0);
            SMS_loadSTMcompressedTileMap(0, 0, mesh_02_tilemap_stmcompr);
            break;

        case 2:
            SMS_loadPSGaidencompressedTiles(mesh_03_tiles_psgcompr, 0);
            SMS_loadSTMcompressedTileMap(0, 0, mesh_03_tilemap_stmcompr);
            break;

        case 3:
            SMS_loadPSGaidencompressedTiles(mesh_04_tiles_psgcompr, 0);
            SMS_loadSTMcompressedTileMap(0, 0, mesh_04_tilemap_stmcompr);
            break;
    }

    if (show_mesh++ > 8 * 4)
        show_mesh = 0;
}
