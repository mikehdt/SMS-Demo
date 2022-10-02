#include "particles.h"
#include "../assets2banks.h" // Generated with the assets task
#include "../engine/palettes.h"
#include "../engine/scenes.h"
#include "../helpers/sintab.h"
#include "../libs/SMSlib.h"
#include <stdint.h>

#define PALMS_OFFSET 57
#define NUM_SPHERES 24
#define NUM_TILES 6
#define X_OFFSET 128
#define Y_OFFSET 64
#define X_BITSHIFT 1
#define Y_BITSHIFT 1
#define Y_RANGE (256 >> Y_BITSHIFT) // sintab range 128:-128 ie. 256

uint16_t count;
uint16_t particle_scroll_x;

struct sphere
{
    int x, y, tx, ty, tile;
};

struct sphere spheres[NUM_SPHERES];

uint8_t cos_lut[256];
uint8_t sin_lut[256];
uint8_t sphere_offset_lut[NUM_SPHERES];
uint16_t sphere_lut[Y_RANGE];

static uint8_t ang_x = 0;
static uint8_t ang_y = 0;
static uint8_t y_range_half = Y_RANGE >> 1;

unsigned char STAGE;

void calc_sphere_sin(void)
{
    uint16_t i;

    for (i = 0; i < 256; i++)
    {
        cos_lut[i] = X_OFFSET + (sintab[i] >> X_BITSHIFT);
        sin_lut[i] = Y_OFFSET + (sintab[i] >> Y_BITSHIFT);

        if (i < Y_RANGE) // Assuming that Y_RANGE will always be less than 256
            sphere_lut[i] = PALMS_OFFSET + ((((abs(i - (Y_RANGE >> 1)) << 8) / (Y_RANGE >> 1)) * NUM_TILES + 128) >> 8);
    }

    for (i = 0; i < NUM_SPHERES; i++)
        sphere_offset_lut[i] = ((i * 256) / NUM_SPHERES);
}

void init_spheres(void)
{
    SMS_initSprites();

    SMS_mapROMBank(spheres_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(spheres_tiles_psgcompr, PALMS_OFFSET);
    SMS_loadSpritePalette(spheres_palette_bin);

    calc_sphere_sin();
}

void animate_spheres(void)
{
    uint8_t i;

    if (STAGE == 1)
    {
        if (count < NUM_SPHERES && frame_count % 2 == 0)
        {
            spheres[count].x = 128;
            spheres[count].y = 96;

            SMS_addSprite(spheres[count].x, spheres[count].y, PALMS_OFFSET);

            count++;
        }

        if (count == NUM_SPHERES)
            STAGE = 2;
    }

    if (STAGE == 1 || STAGE == 2)
    {
        uint8_t sang, cang;

        // Thought: it may just be too slow/messy overall to have spheres
        // always dynamically chase; maybe they just need a "move to new" mode?
        for (i = 0; i < count; i++)
        {
            sang = ang_y + sphere_offset_lut[i];
            cang = ang_x + sang;

            // Chase
            spheres[i].tx = cos_lut[cang];
            spheres[i].ty = sin_lut[sang];

            spheres[i].x += (spheres[i].tx - spheres[i].x) >> 3;
            spheres[i].y += (spheres[i].ty - spheres[i].y) >> 3;

            SMS_updateSpritePosition(i, spheres[i].x, spheres[i].y);

            spheres[i].tile = sphere_lut[spheres[i].y + y_range_half - Y_OFFSET];
            SMS_updateSpriteImage(i, spheres[i].tile);
        }

        ang_x++;
        ang_y++;

        // if (STAGE == 2 && frame_count % 128 == 0)
        //     STAGE = 3;
    }
    else if (STAGE == 3)
    {
        // for (i = 0; i < count; i++)
        // {
        //     if ((i < (count >> 1) && frame_count % 6 == 0) || i >= (count >> 1) && frame_count % 6 == 3)
        //     {
        //         // Some other effect here
        //         spheres[i].tx = (rand() & 192) + 32;
        //         spheres[i].ty = rand() & 128;
        //     }

        //     spheres[i].x += (spheres[i].tx - spheres[i].x) >> 3;
        //     spheres[i].y += (spheres[i].ty - spheres[i].y) >> 3;

        //     SMS_updateSpritePosition(i, spheres[i].x, spheres[i].y);
        // }

        // if (frame_count % 128 == 0)
        //     STAGE = 2;
    }
}

void particles_scene_init(void)
{
    srand(frame_count);

    STAGE = 1;
    count = 0;
    particle_scroll_x = 0;
    ang_x = 0;
    ang_y = 0;

    set_palette(palette_black, PALETTE_BACKGROUND);

    SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK); // Hide stuff for scrolling
    SMS_setBGScrollX(0);
    SMS_mapROMBank(palms_tiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(palms_tiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(0, 0, palms_tilemap_stmcompr);

    fade_to_palette(palms_palette_bin, true);
    init_spheres();
}

void particles_scene_update(void)
{
    SMS_setBGScrollX(particle_scroll_x++ >> 3);

    animate_spheres();
    SMS_waitForVBlank();
    SMS_copySpritestoSAT();
}

void particles_scene_end(void)
{
    for (int i = count; i >= 0; i--)
    {
        SMS_hideSprite(i);
        SMS_waitForVBlank();
        SMS_copySpritestoSAT();
    }

    SMS_initSprites();
    fade_to_palette(palette_black, false);

    SMS_setBGScrollX(0);
    SMS_VDPturnOffFeature(VDPFEATURE_LEFTCOLBLANK); // Hide stuff for scrolling
}
