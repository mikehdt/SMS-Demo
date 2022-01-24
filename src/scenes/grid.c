#include "grid.h"
#include "../assets2banks.h" // Generated with the assets task
#include "../engine/core.h"
#include "../engine/scenes.h"
#include "../libs/SMSlib.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

unsigned int grid_scroll_x = 0;
unsigned int grid_scroll_tick = 0;
char scroll_message[] = "HELLO WORLD, HERES SOME NUMBERS: 01234567890.";
uint16_t scroll_index = 0;
unsigned char scroll_tile_index = 0;

// uint8_t show_mesh = 0;

// This grid thing has been co-opted for typography testing instead :3
#define CHARS_BASE_ADDRESS 1

void print_string(unsigned char x, unsigned char y, unsigned char *string)
{
    unsigned char i, character, string_length = strlen(string);

    i = 0;

    while (i < string_length && i < SCREEN_COLUMNS)
    {
        character = string[i] - 'A';

        switch (character)
        {
            case 32: // Space
                SMS_setTileatXY(x + i, y, 0);
                break;

            default:
                SMS_setTileatXY(x + i, y, CHARS_BASE_ADDRESS + character);
                break;
        }

        i++;
    }
}

void print_string_char(unsigned char x, unsigned char y, unsigned char string_char)
{
    // This is pretty hacky, could be better packed?
    if (string_char == 32 || string_char == 0) // Space
        SMS_setTileatXY(x, y, 0);
    else if (string_char == 44) // Comma
        SMS_setTileatXY(x, y, CHARS_BASE_ADDRESS + 39);
    else if (string_char == 46) // Full stop
        SMS_setTileatXY(x, y, CHARS_BASE_ADDRESS + 38);
    else if (string_char >= 48 && string_char <= 59) // Numbers and :;
        SMS_setTileatXY(x, y, CHARS_BASE_ADDRESS + string_char - '0' + 26);
    else // Base letters
        SMS_setTileatXY(x, y, CHARS_BASE_ADDRESS + string_char - 'A');
}

void grid_scene_init(void)
{
    SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK);
    SMS_loadBGPalette(font_alpha_palette_bin);
    SMS_loadSpritePalette(font_alpha_palette_bin); // temp to see unused tiles
    SMS_loadPSGaidencompressedTiles(font_alpha_tiles_psgcompr, 1);
    // SMS_loadBGPalette(mesh_01_palette_bin);
}

void grid_scene_update(void)
{
    if (grid_scroll_tick++ != 1)
    {
        wait_for_frame();
        return;
    }

    grid_scroll_tick = 0;

    if (grid_scroll_x % 8 == 0)
    {
        print_string_char(scroll_tile_index, 9, scroll_message[scroll_index]);

        // Avoid terminating 0, not sure why it's 2 offset though...
        if (scroll_index++ >= sizeof(scroll_message) - 1)
            scroll_index = 0;

        // Avoid writing past the end of the screen
        if (scroll_tile_index++ >= SCREEN_COLUMNS - 1)
            scroll_tile_index = 0;
    }

    SMS_setBGScrollX(grid_scroll_x);

    grid_scroll_x--;

    wait_for_frame();

    // switch (show_mesh >> 3)
    // {
    //     case 0:
    //         SMS_loadPSGaidencompressedTiles(mesh_01_tiles_psgcompr, 0);
    //         SMS_loadSTMcompressedTileMap(0, 0, mesh_01_tilemap_stmcompr);
    //         break;

    //     case 1:
    //         SMS_loadPSGaidencompressedTiles(mesh_02_tiles_psgcompr, 0);
    //         SMS_loadSTMcompressedTileMap(0, 0, mesh_02_tilemap_stmcompr);
    //         break;

    //     case 2:
    //         SMS_loadPSGaidencompressedTiles(mesh_03_tiles_psgcompr, 0);
    //         SMS_loadSTMcompressedTileMap(0, 0, mesh_03_tilemap_stmcompr);
    //         break;

    //     case 3:
    //         SMS_loadPSGaidencompressedTiles(mesh_04_tiles_psgcompr, 0);
    //         SMS_loadSTMcompressedTileMap(0, 0, mesh_04_tilemap_stmcompr);
    //         break;
    // }

    // if (show_mesh++ > 8 * 4)
    //     show_mesh = 0;
}
