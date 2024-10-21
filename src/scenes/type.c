#include "type.h"
#include "../assets2banks.h"
#include "../engine/global_constants.h"
#include "../engine/palettes.h"
#include "../engine/scenes.h"
#include "../engine/sprites.h"
#include "../engine/tilemap.h"
#include "../helpers/scroll_interrupt.h"
#include "../libs/SMSlib.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint16_t type_scroll_tick, scroll_index, next_type_scroll_value, type_scroll_x[6];
unsigned char scroll_tile_index, type_line_count;

char scroll_message[] = "GREETS TO THE DEMOSCENE AND SMSPOWER :: WELCOME DA BABIES PASCAL AND RAFAEL :: DISASTERAREA 2024                                ";

#define CHARS_BASE_ADDRESS 104
#define CHARS_OFFSET 40

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
                SMS_setTileatXY(x + i, y + 1, 0);
                break;

            default:
                SMS_setTileatXY(x + i, y, CHARS_BASE_ADDRESS + character);
                SMS_setTileatXY(x + i, y + 1, CHARS_OFFSET + CHARS_BASE_ADDRESS + character);
                break;
        }

        i++;
    }
}

void print_string_char(unsigned char x, unsigned char y, unsigned char string_char)
{
    // This is pretty hacky, could be better packed?
    if (string_char == 32 || string_char == 0)
    {
        // Space
        SMS_setTileatXY(x, y, 0);
        SMS_setTileatXY(x, y + 1, 0);
    }
    else if (string_char == 44)
    {
        // Comma
        SMS_setTileatXY(x, y, CHARS_BASE_ADDRESS + 39);
        SMS_setTileatXY(x, y + 1, CHARS_OFFSET + CHARS_BASE_ADDRESS + 39);
    }
    else if (string_char == 46)
    {
        // Full stop
        SMS_setTileatXY(x, y, CHARS_BASE_ADDRESS + 38);
        SMS_setTileatXY(x, y + 1, CHARS_OFFSET + CHARS_BASE_ADDRESS + 38);
    }
    else if (string_char >= 48 && string_char <= 59)
    {
        // Numbers and :;
        SMS_setTileatXY(x, y, CHARS_BASE_ADDRESS + string_char - '0' + 26);
        SMS_setTileatXY(x, y + 1, CHARS_OFFSET + CHARS_BASE_ADDRESS + string_char - '0' + 26);
    }
    else
    {
        // Base letters
        SMS_setTileatXY(x, y, CHARS_BASE_ADDRESS + string_char - 'A');
        SMS_setTileatXY(x, y + 1, CHARS_OFFSET + CHARS_BASE_ADDRESS + string_char - 'A');
    }
}

void update_type_scroll_pos(void)
{
    type_line_count = 0;
    type_scroll_x[3] -= 2;
    next_type_scroll_value = type_scroll_x[0];
}

void type_scroll(void)
{
    SMS_copySpritestoSAT();
    SMS_setLineCounter(15); // Reset

    update_type_scroll_pos();
}

void typeScrollHandler(void)
{
    // SMS_debugPrintf("typelinecount: %d\n", type_line_count);

    INLINE_SMS_setBGScrollX(next_type_scroll_value);

    next_type_scroll_value = type_scroll_x[type_line_count] >> 2;

    if (++type_line_count == 5)
        SMS_setLineCounter(127); // Every n + 1 scanlines (0 indexed)
}

void type_init(void)
{
    cur_stage = 1;
    type_line_count = 0;

    type_scroll_x[0] = 0x0000;
    type_scroll_x[1] = 0x0000;
    type_scroll_x[2] = 0x0000;
    type_scroll_x[3] = 0x0000;
    type_scroll_x[4] = 0x0000;
    next_type_scroll_value = 0x0000;

    type_scroll_tick = 0;
    scroll_index = 0;
    scroll_tile_index = 0;

    SMS_waitForVBlank();

    SMS_setBGScrollX(0);
    SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK);

    SMS_mapROMBank(font_beta_palette_bin_bank);
    SMS_loadBGPalette(font_beta_palette_bin);
    SMS_loadPSGaidencompressedTiles(font_beta_tiles_psgcompr, 104);

    clear_tilemap(0);

    SMS_loadSpritePalette(palette_black);
    SMS_loadPSGaidencompressedTiles(lady_mini_tiles_psgcompr, 0);
    SMS_loadPSGaidencompressedTiles(lady_mini_eyes_tiles_psgcompr, 192);
    SMS_loadPSGaidencompressedTiles(lady_mini_spr_tiles_psgcompr, 256); // urgh sprites
    SMS_loadSTMcompressedTileMap(12, 0, lady_mini_tilemap_stmcompr);

    // Row 1
    SMS_setTileatXY(12, 10, 0);
    SMS_setTileatXY(13, 10, 0);
    SMS_setTileatXY(14, 10, 0);
    SMS_setTileatXY(15, 10, 0);
    SMS_setTileatXY(16, 10, 0);
    SMS_setTileatXY(17, 10, 0);
    SMS_setTileatXY(18, 10, 0);
    SMS_addSprite(12 * 8 + 4, 10 * 8, 0);
    SMS_addSprite(13 * 8 + 4, 10 * 8, 1);
    SMS_addSprite(14 * 8 + 4, 10 * 8, 2);
    SMS_addSprite(15 * 8 + 4, 10 * 8, 3);
    SMS_addSprite(16 * 8 + 4, 10 * 8, 4);
    SMS_addSprite(17 * 8 + 4, 10 * 8, 5);
    // Row 2
    SMS_setTileatXY(12, 11, 0);
    SMS_setTileatXY(13, 11, 0);
    SMS_setTileatXY(14, 11, 0);
    SMS_setTileatXY(15, 11, 0);
    SMS_setTileatXY(16, 11, 0);
    SMS_setTileatXY(17, 11, 0);
    SMS_setTileatXY(18, 11, 0);
    SMS_addSprite(12 * 8 + 4, 11 * 8, 6);
    SMS_addSprite(13 * 8 + 4, 11 * 8, 7);
    SMS_addSprite(14 * 8 + 4, 11 * 8, 8);
    SMS_addSprite(15 * 8 + 4, 11 * 8, 9);
    SMS_addSprite(16 * 8 + 4, 11 * 8, 10);
    SMS_addSprite(17 * 8 + 4, 11 * 8, 11);

    SMS_copySpritestoSAT();
}

void type_update(void)
{
    SMS_waitForVBlank();

    if (cur_stage == 1)
    {
        for (uint8_t i = 0; i < 10; i++)
        {
            fade_sprite_from_black(lady_mini_palette_bin, i);

            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
        }

        set_scroll(20, &typeScrollHandler);
        update_type_scroll_pos();
        cur_stage = 2;
    }
    else
    {
        // Implicit cur_stage == 2
        uint8_t cur_frame_modulo = cur_frame % 59;

        if (cur_frame_modulo == 1)
        {
            // Blink third eye
            SMS_setTileatXY(15, 1, 192 | TILE_USE_SPRITE_PALETTE);
        }
        else if (cur_frame_modulo == 5)
        {
            // Blink normal eyes
            SMS_setTileatXY(14, 2, 193 | TILE_USE_SPRITE_PALETTE);
            SMS_setTileatXY(15, 2, 194 | TILE_USE_SPRITE_PALETTE);
            SMS_setTileatXY(16, 2, 195 | TILE_USE_SPRITE_PALETTE);
        }
        else if (cur_frame_modulo == 6)
        {
            // Open third eye
            SMS_setTileatXY(15, 1, 5 | TILE_USE_SPRITE_PALETTE);
        }
        else if (cur_frame_modulo == 9)
        {
            // Open normal eyes
            SMS_setTileatXY(14, 2, 8 | TILE_USE_SPRITE_PALETTE);
            SMS_setTileatXY(15, 2, 9 | TILE_USE_SPRITE_PALETTE);
            SMS_setTileatXY(16, 2, 10 | TILE_USE_SPRITE_PALETTE);
        }
    }

    type_scroll();

    if (type_scroll_tick++ != 1 || scroll_index >= sizeof(scroll_message)) // Second part is to indefinitely hold the end
        return;

    type_scroll_tick = 0;

    if ((type_scroll_x[3] - 2) % 32 == 0)
    {
        // SMS_debugPrintf("typescrollx: %d %d\n", scroll_tile_index, scroll_message[scroll_index]);

        // DO NOT ASK ME ABOUT WHY THIS IS I HAVE NO CLUE
        if (scroll_tile_index == 31)
            print_string_char(scroll_tile_index + 1, 9, scroll_message[scroll_index]);
        else
            print_string_char(scroll_tile_index + 1, 10, scroll_message[scroll_index]);

        scroll_index++;

        // Avoid terminating 0, not sure why it's 2 offset though...
        if (cur_stage == 2 && scroll_index >= sizeof(scroll_message))
        {
            clear_scroll();

            for (uint8_t i = 0; i < 10; i++)
            {
                fade_sprite_to_black(lady_mini_palette_bin, i);

                SMS_waitForVBlank();
                SMS_waitForVBlank();
                SMS_waitForVBlank();
                SMS_waitForVBlank();
                SMS_waitForVBlank();
                SMS_waitForVBlank();
                SMS_waitForVBlank();
                SMS_waitForVBlank();
            }

            cur_stage = 3;

            // next_scene();
        }

        // Avoid writing past the end of the screen
        if (++scroll_tile_index >= SCREEN_COLUMNS)
            scroll_tile_index = 0;
    }

    cur_frame++;
}

void type_end(void)
{
    SMS_waitForVBlank();
    clear_tilemap(0);
    clear_sprites();
    clear_scroll();

    SMS_VDPturnOffFeature(VDPFEATURE_LEFTCOLBLANK);
    SMS_setBGScrollX(0);
}
