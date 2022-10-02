#include "type.h"
#include "../assets2banks.h" // Generated with the assets task
#include "../engine/globals.h"
#include "../engine/scenes.h"
#include "../engine/tilemap.h"
#include "../libs/SMSlib.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint16_t type_scroll_x = 0;
uint16_t type_scroll_tick = 0;
uint16_t scroll_index = 0;
char scroll_message[] = "HELLO WORLD, HERES SOME NUMBERS: 01234567890.";
unsigned char scroll_tile_index = 0;

#define CHARS_BASE_ADDRESS 0

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
        SMS_setTileatXY(x, y, 40);
    else if (string_char == 44) // Comma
        SMS_setTileatXY(x, y, CHARS_BASE_ADDRESS + 39);
    else if (string_char == 46) // Full stop
        SMS_setTileatXY(x, y, CHARS_BASE_ADDRESS + 38);
    else if (string_char >= 48 && string_char <= 59) // Numbers and :;
        SMS_setTileatXY(x, y, CHARS_BASE_ADDRESS + string_char - '0' + 26);
    else // Base letters
        SMS_setTileatXY(x, y, CHARS_BASE_ADDRESS + string_char - 'A');
}

void type_scene_init(void)
{
    SMS_setBGScrollX(0);
    SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK);
    SMS_mapROMBank(font_alpha_palette_bin_bank);
    SMS_loadBGPalette(font_alpha_palette_bin);
    SMS_loadSpritePalette(font_alpha_palette_bin);
    SMS_loadPSGaidencompressedTiles(font_alpha_tiles_psgcompr, 0);

    SMS_mapROMBank(blank_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(blank_tiles_psgcompr, 40);

    clear_tilemap(40);
}

void type_scene_update(void)
{
    SMS_waitForVBlank();

    if (type_scroll_tick++ != 1)
        return;

    type_scroll_tick = 0;

    if (type_scroll_x % 8 == 0)
    {
        print_string_char(scroll_tile_index, 9, scroll_message[scroll_index]);

        // Avoid terminating 0, not sure why it's 2 offset though...
        if (scroll_index++ >= sizeof(scroll_message) - 1)
            scroll_index = 0;

        // Avoid writing past the end of the screen
        if (scroll_tile_index++ >= SCREEN_COLUMNS - 1)
            scroll_tile_index = 0;
    }

    SMS_setBGScrollX(type_scroll_x);

    type_scroll_x--;
}

void type_scene_end(void)
{
    SMS_waitForVBlank();
    SMS_setBGScrollX(0);
    SMS_VDPturnOffFeature(VDPFEATURE_LEFTCOLBLANK);
}
