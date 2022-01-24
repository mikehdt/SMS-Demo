#include "picture.h"
#include "../assets2banks.h" // Generated with the assets task
#include "../engine/core.h"
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

unsigned int count;
unsigned int scroll_x;

struct sphere
{
    int x, y, tx, ty, tile;
};

struct sphere spheres[NUM_SPHERES];

uint8_t cos_lut[256];
uint8_t sin_lut[256];
uint16_t sphere_lut[Y_RANGE];

static uint8_t ang_x = 0;
static uint8_t ang_y = 0;

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
}

void init_spheres(void)
{
    SMS_initSprites();
    SMS_loadPSGaidencompressedTiles(spheres_tiles_psgcompr, PALMS_OFFSET);
    SMS_loadSpritePalette(palms_palette_bin);

    calc_sphere_sin();
}

void animate_spheres(void)
{
    unsigned int i;

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
        uint8_t sang, cang, new_tile;

        for (i = 0; i < count; i++)
        {
            sang = ang_y + ((i * 256) / NUM_SPHERES);
            cang = ang_x + sang;

            // Chase
            spheres[i].tx = cos_lut[cang];
            spheres[i].ty = sin_lut[sang];

            spheres[i].x += (spheres[i].tx - spheres[i].x) >> 3;
            spheres[i].y += (spheres[i].ty - spheres[i].y) >> 3;

            SMS_updateSpritePosition(i, spheres[i].x, spheres[i].y);

            new_tile = sphere_lut[spheres[i].y + (Y_RANGE >> 1) - Y_OFFSET];

            if (spheres[i].tile != new_tile)
            {
                spheres[i].tile = new_tile;
                SMS_updateSpriteImage(i, new_tile);
            }
        }

        ang_x++;
        ang_y++;

        if (frame_count % 128 == 0)
        {
            STAGE = 3;
        }
    }
    else if (STAGE == 3)
    {

        for (i = 0; i < count; i++)
        {
            if ((i < (count / 2) && frame_count % 6 == 0) || i >= (count / 2) && frame_count % 6 == 3)
            {
                // Some other effect here
                spheres[i].tx = rand() % 192 + 32;
                spheres[i].ty = rand() % 128;
            }

            spheres[i].x += (spheres[i].tx - spheres[i].x) >> 3;
            spheres[i].y += (spheres[i].ty - spheres[i].y) >> 3;

            SMS_updateSpritePosition(i, spheres[i].x, spheres[i].y);
        }

        if (frame_count % 128 == 0)
        {
            STAGE = 2;
        }
    }
}

void picture_scene_init(void)
{
    srand(frame_count);

    STAGE = 1;
    count = 0;
    scroll_x = 0;
    ang_x = 0;
    ang_y = 0;

    set_palette(palette_black, PALETTE_BACKGROUND);

    SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK); // Hide stuff for scrolling
    SMS_setBGScrollX(0);
    SMS_loadPSGaidencompressedTiles(palms_tiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(0, 0, palms_tilemap_stmcompr);

    fade_to_palette(palms_palette_bin, true);
    init_spheres();
}

void picture_scene_update(void)
{
    SMS_setBGScrollX(scroll_x++ >> 3);

    animate_spheres();
    wait_for_frame();
}

void picture_scene_end(void)
{
    for (int i = count; i >= 0; i--)
    {
        SMS_hideSprite(i);
        wait_for_frame();
    }

    SMS_initSprites();
    fade_to_palette(palette_black, false);

    SMS_setBGScrollX(0);
    SMS_VDPturnOffFeature(VDPFEATURE_LEFTCOLBLANK); // Hide stuff for scrolling
}
