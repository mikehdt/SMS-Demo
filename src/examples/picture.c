#include "picture.h"
#include "../assets2banks.h" // Generated with the assets task
#include "../libs/SMSlib.h"

#define TEST_OFFSET 57
#define NUM_SPHERES 7

unsigned int scroll_x;

struct sphere
{
    char id;
    int x, y;
};

struct sphere spheres[NUM_SPHERES];

void init_picture(void)
{
    int i = 0;

    SMS_loadPSGaidencompressedTiles(test_tiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(0, 0, test_tilemap_stmcompr);
    SMS_loadBGPalette(test_palette_bin);

    SMS_loadPSGaidencompressedTiles(spheres_tiles_psgcompr, TEST_OFFSET);

    SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK); // Hide stuff for scrolling

    scroll_x = 0;
}

void init_sprites(void)
{
    int i = 0;

    SMS_loadSpritePalette(test_palette_bin);
    SMS_initSprites();

    for (i = 0; i < NUM_SPHERES; i++)
    {
        spheres[i].id = SMS_addSprite(i * 10, i * 10, TEST_OFFSET + NUM_SPHERES - i - 1);
        spheres[i].x = i * 10;
        spheres[i].y = i * 10;
        // If the return is -1, no more sprites could be allocated
        // If the return is -2, the y-coordinate is invalid
    }
}

void animate_picture(void)
{
    SMS_setBGScrollX(scroll_x++ >> 3);
}

void animate_sprites(void)
{
    unsigned int i;

    for (i = 0; i < NUM_SPHERES; i++)
    {
        SMS_updateSpritePosition(spheres[i].id, spheres[i].x, spheres[i].y);

        if (spheres[i].x++ > 256)
            spheres[i].x = 0;
        if (spheres[i].y++ > 192)
            spheres[i].y = 0;
    }
}
