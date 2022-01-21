#include "picture.h"
#include "../assets2banks.h" // Generated with the assets task
#include "../engine/core.h"
#include "../engine/palettes.h"
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

unsigned int scroll_x;

struct sphere
{
    int x, y, sphere_tile;
};

struct sphere spheres[NUM_SPHERES];

uint8_t sphere_cosangles[256];
uint8_t sphere_sinangles[256];
uint16_t ytab[Y_RANGE];

static uint8_t ang_x = 0;
static uint8_t ang_y = 0;

void init_sphere_sin(void)
{
    uint16_t i;

    for (i = 0; i < 256; i++)
    {
        sphere_cosangles[i] = X_OFFSET + (sintab[i] >> X_BITSHIFT);
        sphere_sinangles[i] = Y_OFFSET + (sintab[i] >> Y_BITSHIFT);

        if (i < Y_RANGE) // Assuming that Y_RANGE will always be less than 256
            ytab[i] = PALMS_OFFSET + ((((abs(i - (Y_RANGE >> 1)) << 8) / (Y_RANGE >> 1)) * NUM_TILES + 128) >> 8);
    }
}

void init_spheres(void)
{
    SMS_initSprites();
    SMS_loadPSGaidencompressedTiles(spheres_tiles_psgcompr, PALMS_OFFSET);
    SMS_loadSpritePalette(palms_palette_bin);

    init_sphere_sin();

    for (uint8_t i = 0; i < NUM_SPHERES; i++)
    {
        spheres[i].x = 0;
        spheres[i].y = 0;

        SMS_addSprite(0, 0, PALMS_OFFSET);
    }
}

void animate_spheres(void)
{
    unsigned int i;

    for (i = 0; i < NUM_SPHERES; i++)
    {
        uint8_t sang = ang_y + ((i * 256) / NUM_SPHERES);
        uint8_t cang = ang_x + sang; // + 64?
        spheres[i].x = sphere_cosangles[cang];
        spheres[i].y = sphere_sinangles[sang];

        SMS_updateSpritePosition(i, spheres[i].x, spheres[i].y);
        SMS_updateSpriteImage(i, ytab[spheres[i].y + (Y_RANGE >> 1) - Y_OFFSET]);
    }

    ang_x++;
    ang_y++;
}

void picture_scene_init(void)
{
    scroll_x = 0;

    set_palette(palette_black, PALETTE_BACKGROUND);

    SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK); // Hide stuff for scrolling
    SMS_setBGScrollX(0);
    SMS_loadPSGaidencompressedTiles(palms_tiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(0, 0, palms_tilemap_stmcompr);

    fade_to_palette(palms_palette_bin, true);
    // fade_from_black(palms_palette_bin);

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
    SMS_initSprites();
    fade_to_palette(palette_black, false);

    SMS_setBGScrollX(0);
    SMS_VDPturnOffFeature(VDPFEATURE_LEFTCOLBLANK); // Hide stuff for scrolling
}
