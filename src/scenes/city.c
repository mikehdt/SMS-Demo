#include "city.h"
#include "../assets2banks.h"
#include "../engine/global_constants.h"
#include "../engine/palettes.h"
#include "../engine/scenes.h"
#include "../engine/sprites.h"
#include "../helpers/ps_rand.h"
#include "../helpers/scroll_interrupt.h"
#include "../helpers/sintab.h"
#include "../libs/SMSlib.h"
#include <stdint.h>

// Scroller defs
#define CITY_TILE_COUNT 256 // So the sprites can be placed from this point on

unsigned char city_line_count = 0;
uint8_t fade_count;
uint16_t next_city_scroll_value, city_scroll_x[3];

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
    if (cur_stage == 4)
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
        {
            cur_frame = 0;
            cur_stage = 5;
        }
    }

    if (cur_stage == 4 || cur_stage == 5)
    {
        uint8_t i, s_ang, c_ang;

        for (i = 0; i < sphere_count; i++)
        {
            s_ang = ang_y + sphere_offset_lut[i];
            c_ang = ang_x + s_ang;

            // Chase
            spheres[i].tx = cos_lut[c_ang] - 63;
            spheres[i].ty = sin_lut[s_ang] - 63;

            spheres[i].x += (spheres[i].tx - spheres[i].x) >> 3 - 1;
            spheres[i].y += (spheres[i].ty - spheres[i].y) >> 3 - 1;
            spheres[i].tile = sphere_lut[spheres[i].y - Y_OFFSET + Y_RANGE_HALF];

            SMS_updateSpritePosition(i, spheres[i].x, spheres[i].y);
            SMS_updateSpriteImage(i, spheres[i].tile);
        }

        ang_x++;
        ang_y++;

        if (cur_stage == 5 && cur_frame > 90)
        {
            cur_stage = 6;
        }
    }

    if (cur_stage == 6)
    {
        uint8_t i;

        for (i = 0; i < sphere_count; i++)
        {
            // Chase
            spheres[i].tx = ps_rand() * 2;
            spheres[i].ty = ps_rand() * 2;
        }

        cur_frame = 0;
        cur_stage = 7;
    }

    if (cur_stage == 7)
    {
        uint8_t i;

        for (i = 0; i < sphere_count; i++)
        {
            spheres[i].x += (spheres[i].tx - spheres[i].x) >> 7;
            spheres[i].y += (spheres[i].ty - spheres[i].y) >> 7;
            spheres[i].tile = sphere_lut[spheres[i].y - Y_OFFSET + Y_RANGE_HALF];

            SMS_updateSpritePosition(i, spheres[i].x, spheres[i].y);
            SMS_updateSpriteImage(i, spheres[i].tile);
        }

        if (cur_frame == 45)
        {
            cur_stage = 1;
            next_scene();
        }
    }
}

// Background mover
void cityScrollHandler(void)
{
    INLINE_SMS_setBGScrollX(next_city_scroll_value);

    next_city_scroll_value = city_scroll_x[city_line_count] >> 5;

    if (++city_line_count == 3)
        SMS_setLineCounter(127); // Every n + 1 scanlines (0 indexed)
}

void update_scroll_pos(void)
{
    city_line_count = 0;
    city_scroll_x[0] += 3;
    city_scroll_x[1] += 2;
    city_scroll_x[2] += 1;
    next_city_scroll_value = city_scroll_x[0] >> 5;
}

void city_init(void)
{
    SMS_displayOff();
    SMS_waitForVBlank();
    SMS_mapROMBank(cityscape_palette_bin_bank);
    SMS_loadSTMcompressedTileMap(0, 0, cityscape_tilemap_stmcompr);

    if (cur_stage == 1)
    {
        // Sprites
        ang_x = 0;
        ang_y = 0;

        calc_sphere_sin();

        // Scroller and background
        fade_count = 0;

        city_scroll_x[0] = 0xFFFF;
        city_scroll_x[1] = 0xFFFF;
        city_scroll_x[2] = 0xFFFF;
        next_city_scroll_value = 0xFFFF;

        load_palette(palette_black, PALETTE_BACKGROUND);

        SMS_loadPSGaidencompressedTiles(cityscape_tiles_psgcompr, 0);
    }
    else if (cur_stage == 3)
    {
        SMS_initSprites();
        SMS_loadPSGaidencompressedTiles(spheres_tiles_psgcompr, CITY_TILE_COUNT);
        load_palette(spheres_palette_bin, PALETTE_SPRITE);
    }

    set_scroll(15, &cityScrollHandler);
    update_scroll_pos();

    SMS_waitForVBlank();
    SMS_displayOn();
}

void city_scroll(void)
{
    SMS_copySpritestoSAT();
    SMS_setLineCounter(15); // Reset

    update_scroll_pos();
}

void city_update(void)
{
    if (cur_stage == 1)
    {
        if (cur_frame == 40 && fade_count < 3)
        {
            fade_from_black(cityscape_palette_bin, fade_count);

            fade_count++;
            cur_frame = 0;
        }
        else if (cur_frame > 120)
        {
            cur_stage = 2;
            next_scene();
        }
    }
    else if (cur_stage == 2)
    {
        if (cur_frame >= 40)
        {
            fade_from_black(cityscape_palette_bin, fade_count);
            fade_count++;
            cur_frame = 0;

            if (fade_count > 6)
            {
                cur_stage = 3;
                next_scene();
            }
        }
    }
    else if (cur_stage == 3)
    {
        if (cur_frame == 40)
        {
            fade_from_black(cityscape_palette_bin, fade_count);
            fade_count++;
            cur_frame = 0;

            if (fade_count > 9)
                cur_stage = 4;
        }
    }

    SMS_waitForVBlank();
    city_scroll();
    animate_spheres();

    cur_frame++;
}

void city_end(void)
{
    SMS_displayOff();
    SMS_waitForVBlank();

    clear_scroll();
    clear_sprites();
    SMS_waitForVBlank();
    SMS_displayOn();
}
