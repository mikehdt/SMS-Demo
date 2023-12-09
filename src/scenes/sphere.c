#include "sphere.h"
#include "../assets2banks.h" // Generated with the assets task
#include "../engine/palettes.h"
#include "../engine/tilemap.h"
#include "../libs/SMSlib.h"

int cur_pal = 0;

const unsigned char sphere_palette[] = {
    // 1
    0x06, 0x06, 0x1A, 0x1A,
    0x06, 0x06, 0x1A, 0x1A,
    0x1A, 0x1A, 0x06, 0x06,
    0x1A, 0x1A, 0x06, 0x06,
    // 2
    0x1A, 0x06, 0x06, 0x1A,
    0x1A, 0x06, 0x06, 0x1A,
    0x06, 0x1A, 0x1A, 0x06,
    0x06, 0x1A, 0x1A, 0x06,
    // 3
    0x1A, 0x1A, 0x06, 0x06,
    0x1A, 0x1A, 0x06, 0x06,
    0x06, 0x06, 0x1A, 0x1A,
    0x06, 0x06, 0x1A, 0x1A,
    // 4
    0x06, 0x1A, 0x1A, 0x06,
    0x06, 0x1A, 0x1A, 0x06,
    0x1A, 0x06, 0x06, 0x1A,
    0x1A, 0x06, 0x06, 0x1A,
    // 5
    0x06, 0x06, 0x1A, 0x1A,
    0x06, 0x06, 0x1A, 0x1A,
    0x1A, 0x1A, 0x06, 0x06,
    0x1A, 0x1A, 0x06, 0x06,
    // 6
    0x1A, 0x1A, 0x06, 0x06,
    0x06, 0x06, 0x1A, 0x1A,
    0x06, 0x06, 0x1A, 0x1A,
    0x1A, 0x1A, 0x06, 0x06,
    // 7
    0x1A, 0x1A, 0x06, 0x06,
    0x1A, 0x1A, 0x06, 0x06,
    0x06, 0x06, 0x1A, 0x1A,
    0x06, 0x06, 0x1A, 0x1A,
    // 8
    0x06, 0x06, 0x1A, 0x1A,
    0x1A, 0x1A, 0x06, 0x06,
    0x1A, 0x1A, 0x06, 0x06,
    0x06, 0x06, 0x1A, 0x1A,
    // 9
    0x06, 0x06, 0x1A, 0x1A,
    0x06, 0x06, 0x1A, 0x1A,
    0x1A, 0x1A, 0x06, 0x06,
    0x1A, 0x1A, 0x06, 0x06,
    // 10
    0x06, 0x1A, 0x1A, 0x06,
    0x06, 0x1A, 0x1A, 0x06,
    0x1A, 0x06, 0x06, 0x1A,
    0x1A, 0x06, 0x06, 0x1A,
    // 11
    0x1A, 0x1A, 0x06, 0x06,
    0x1A, 0x1A, 0x06, 0x06,
    0x06, 0x06, 0x1A, 0x1A,
    0x06, 0x06, 0x1A, 0x1A,
    // 12
    0x1A, 0x06, 0x06, 0x1A,
    0x1A, 0x06, 0x06, 0x1A,
    0x06, 0x1A, 0x1A, 0x06,
    0x06, 0x1A, 0x1A, 0x06,
    // 13
    0x06, 0x06, 0x1A, 0x1A,
    0x06, 0x06, 0x1A, 0x1A,
    0x1A, 0x1A, 0x06, 0x06,
    0x1A, 0x1A, 0x06, 0x06,
    // 14
    0x06, 0x06, 0x1A, 0x1A,
    0x1A, 0x1A, 0x06, 0x06,
    0x1A, 0x1A, 0x06, 0x06,
    0x06, 0x06, 0x1A, 0x1A,
    // 15
    0x1A, 0x1A, 0x06, 0x06,
    0x1A, 0x1A, 0x06, 0x06,
    0x06, 0x06, 0x1A, 0x1A,
    0x06, 0x06, 0x1A, 0x1A,
    // 16
    0x1A, 0x1A, 0x06, 0x06,
    0x06, 0x06, 0x1A, 0x1A,
    0x06, 0x06, 0x1A, 0x1A,
    0x1A, 0x1A, 0x06, 0x06};

int last_subset_ptr = -1;

void init_background(void)
{
    uint16_t bg_tile = 121 | TILE_USE_SPRITE_PALETTE | TILE_PRIORITY;

    // Background
    SMS_mapROMBank(blank_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(blank_tiles_psgcompr, 121);

    SMS_mapROMBank(palms_palette_bin_bank);
    SMS_loadSpritePalette(palms_palette_bin);
    SMS_setSpritePaletteColor(0, 0x10);

    clear_tilemap(bg_tile);

    // Sphere
    SMS_mapROMBank(sphere_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(sphere_tiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(10, 5, sphere_tilemap_stmcompr);

    // Tidy-up
    // TL
    SMS_setTileatXY(10, 5, bg_tile);
    SMS_setTileatXY(11, 5, bg_tile);
    SMS_setTileatXY(10, 6, bg_tile);
    SMS_setTileatXY(11, 6, bg_tile);
    // TR
    SMS_setTileatXY(20, 5, bg_tile);
    SMS_setTileatXY(21, 5, bg_tile);
    SMS_setTileatXY(20, 6, bg_tile);
    SMS_setTileatXY(21, 6, bg_tile);
    // BL
    SMS_setTileatXY(10, 15, bg_tile);
    SMS_setTileatXY(11, 15, bg_tile);
    SMS_setTileatXY(10, 16, bg_tile);
    SMS_setTileatXY(11, 16, bg_tile);
    // BR
    SMS_setTileatXY(20, 15, bg_tile);
    SMS_setTileatXY(21, 15, bg_tile);
    SMS_setTileatXY(20, 16, bg_tile);
    SMS_setTileatXY(21, 16, bg_tile);
}

void init_sphere_sprites(void)
{
    // Clipping sprites
    SMS_loadPSGaidencompressedTiles(sphere_clip_tiles_psgcompr, 122);

    // // Clipping sprites
    // // First row
    // SMS_addSprite(12 * 8, 5 * 8, 123);
    // SMS_addSprite(14 * 8, 5 * 8, 124);
    // SMS_addSprite(16 * 8, 5 * 8, 125);
    // SMS_addSprite(18 * 8, 5 * 8, 126);
    // // Second Row
    // SMS_addSprite(10 * 8, 7 * 8, 127);
    // SMS_addSprite(20 * 8, 7 * 8, 128);
    // // Third Row
    // SMS_addSprite(10 * 8, 9 * 8, 129);
    // SMS_addSprite(20 * 8, 9 * 8, 130);
    // // Fourth Row
    // SMS_addSprite(10 * 8, 11 * 8, 131);
    // SMS_addSprite(20 * 8, 11 * 8, 132);
    // // Fifth Row
    // SMS_addSprite(10 * 8, 13 * 8, 133);
    // SMS_addSprite(20 * 8, 13 * 8, 134);
    // // Sixth Row
    // SMS_addSprite(12 * 8, 15 * 8, 135);
    // SMS_addSprite(14 * 8, 15 * 8, 136);
    // SMS_addSprite(16 * 8, 15 * 8, 137);
    // SMS_addSprite(18 * 8, 15 * 8, 138);
}

void sphere_init(void)
{
    SMS_displayOff();
    SMS_initSprites();
    SMS_setSpriteMode(SPRITEMODE_ZOOMED);

    init_background();
    init_sphere_sprites();
    SMS_copySpritestoSAT();
    SMS_waitForVBlank();

    SMS_displayOn();
}

void sphere_update(void)
{
    unsigned char temporal_palette[16];
    unsigned char i;

    int subset_ptr = cur_pal >> 3;

    if (++cur_pal >= 16 * 8)
    {
        cur_pal = 0;
    }

    // Waiting first may be undesirable... to check further
    SMS_waitForVBlank();

    if (last_subset_ptr == subset_ptr)
        return; // Don't update the palette, it hasn't changed
    else
        last_subset_ptr = subset_ptr;

    for (i = 0; i < 16; i++)
    {
        temporal_palette[i] = sphere_palette[(subset_ptr * 16) + i];
    }

    SMS_loadBGPalette(temporal_palette);
}

void sphere_end(void)
{
    SMS_waitForVBlank();

    set_palette(palette_black, PALETTE_BOTH);
    SMS_initSprites();
    SMS_copySpritestoSAT(); // Feels weird that I have to do this _as well_
    SMS_setSpriteMode(SPRITEMODE_NORMAL);

    SMS_waitForVBlank();

    clear_tilemap(0);
}
