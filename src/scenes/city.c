#include "city.h"
#include "../assets2banks.h"
#include "../engine/global_constants.h"
#include "../engine/palettes.h"
#include "../engine/scenes.h"
#include "../engine/sprites.h"
#include "../helpers/scroll_interrupt.h"
#include "../helpers/sintab.h"
#include "../libs/SMSlib.h"
#include <stdint.h>

// Scroller defs
#define CITY_TILE_COUNT 256 // So the sprites can be placed from this point on

unsigned char cityLineCnt = 0;
uint8_t fade_count;
uint16_t next_scroll_value, city_scroll_x[3];

// Particle defs
#define NUM_SPHERES 24
#define NUM_SPRITE_TILES (9 - 1) // 0 indexed
#define X_OFFSET 128
#define Y_OFFSET 80
#define X_BITSHIFT 1
#define Y_BITSHIFT 1
#define Y_RANGE (256 >> Y_BITSHIFT) // sintab range 128:-128 ie. 256
#define Y_RANGE_HALF (Y_RANGE >> 1)

struct sphere
{
    int x, y, tx, ty, tile;
};

struct sphere spheres[NUM_SPHERES];

uint8_t sphere_count = 0,
        cos_lut[256],
        sin_lut[256],
        sphere_offset_lut[NUM_SPHERES];
uint16_t sphere_lut[Y_RANGE];

static uint8_t ang_x = 0,
               ang_y = 0;

// Sphere sine movement
void calc_sphere_sin(void)
{
    uint16_t i;

    for (i = 0; i < 256; i++)
    {
        uint8_t sphere_lut_tmp;
        cos_lut[i] = X_OFFSET + (sintab[i] >> X_BITSHIFT);
        sin_lut[i] = Y_OFFSET + (sintab[i] >> Y_BITSHIFT);

        // Create sphere tile lookup
        if (i <= Y_RANGE)
        {
            sphere_lut_tmp = (((abs(i - Y_RANGE_HALF + 1) << 8) / Y_RANGE_HALF) * NUM_SPRITE_TILES + Y_RANGE) >> 8;

            // Assuming that Y_RANGE will always be less than 256
            sphere_lut[i] = CITY_TILE_COUNT + sphere_lut_tmp;
        }
    }

    for (i = 0; i < NUM_SPHERES; i++)
        sphere_offset_lut[i] = ((i * 256) / NUM_SPHERES);
}

void animate_spheres(void)
{
    // This code is a bit of a mess, but I'm just playing around with it :)
    if (cur_stage == 2)
    {
        if (sphere_count < NUM_SPHERES && cur_frame == 2)
        {
            spheres[sphere_count].x = X_OFFSET;
            spheres[sphere_count].y = Y_OFFSET;

            SMS_addSprite(spheres[sphere_count].x, spheres[sphere_count].y, CITY_TILE_COUNT);

            cur_frame = 0;
            sphere_count++;
        }

        if (sphere_count == NUM_SPHERES)
            cur_stage = 3;
    }

    if (cur_stage >= 2)
    {
        uint8_t i, sang, cang;

        for (i = 0; i < sphere_count; i++)
        {
            sang = ang_y + sphere_offset_lut[i];
            cang = ang_x + sang;

            // Chase
            spheres[i].tx = cos_lut[cang] - 63;
            spheres[i].ty = sin_lut[sang] - 63;

            spheres[i].x += (spheres[i].tx - spheres[i].x) >> 3 - 1;
            spheres[i].y += (spheres[i].ty - spheres[i].y) >> 3 - 1;
            spheres[i].tile = sphere_lut[spheres[i].y - Y_OFFSET + Y_RANGE_HALF];

            SMS_updateSpritePosition(i, spheres[i].x, spheres[i].y);
            SMS_updateSpriteImage(i, spheres[i].tile);
        }

        ang_x++;
        ang_y++;
    }
}

// Background mover
void cityScrollHandler(void)
{
    INLINE_SMS_setBGScrollX(next_scroll_value);

    next_scroll_value = city_scroll_x[cityLineCnt] >> 5;

    if (++cityLineCnt == 3)
        SMS_setLineCounter(127); // Every n + 1 scanlines (0 indexed)
}

void update_scroll_pos(void)
{
    cityLineCnt = 0;
    city_scroll_x[0] += 3;
    city_scroll_x[1] += 2;
    city_scroll_x[2] += 1;
    next_scroll_value = city_scroll_x[0] >> 5;
}

void city_init(void)
{
    cur_stage = 1;
    cur_frame = 0;
    fade_count = 0;

    // Sprites
    ang_x = 0;
    ang_y = 0;

    calc_sphere_sin();

    SMS_initSprites();
    SMS_mapROMBank(spheres_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(spheres_tiles_psgcompr, CITY_TILE_COUNT);
    load_palette(spheres_palette_bin, PALETTE_SPRITE);

    // Scroller and background
    city_scroll_x[0] = 0xFFFF;
    city_scroll_x[1] = 0xFFFF;
    city_scroll_x[2] = 0xFFFF;
    next_scroll_value = 0xFFFF;

    SMS_waitForVBlank();
    load_palette(palette_black, PALETTE_BACKGROUND);

    SMS_mapROMBank(cityscape_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(cityscape_tiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(0, 0, cityscape_tilemap_stmcompr);

    set_scroll(15, &cityScrollHandler);
    update_scroll_pos();
}

void city_scroll(void)
{

    SMS_copySpritestoSAT();
    SMS_setLineCounter(15); // Reset

    update_scroll_pos();
}

void city_update(void)
{
    if (cur_stage == 1 && cur_frame == 30)
    {
        fade_from_black(cityscape_palette_bin, fade_count);
        fade_count++;
        cur_frame = 0;

        if (fade_count >= 10)
            cur_stage = 2;
    }

    if (cur_stage == 3 && cur_frame == 300)
    {
        next_scene();
    }

    SMS_waitForVBlank();
    city_scroll();
    animate_spheres();

    cur_frame++;
}

void city_end(void)
{
    for (int i = sphere_count; i >= 0; i--)
    {
        SMS_waitForVBlank();
        SMS_hideSprite(i);

        city_scroll();
    }

    for (int i = 0; i < 10; i++)
    {
        fade_to_black(cityscape_palette_bin, i);

        SMS_waitForVBlank();
        city_scroll();
        SMS_waitForVBlank();
        city_scroll();
        SMS_waitForVBlank();
        city_scroll();
    }

    SMS_waitForVBlank();

    clear_scroll();
    clear_sprites();
}
