#include "picture.h"
#include "../assets2banks.h" // Generated with the assets task
#include "../libs/SMSlib.h"

#define TEST_OFFSET 57
#define NUM_SPHERES 7
#define SPHERE_TILES 6 // 0-offset to save a -1 later

unsigned int scroll_x;

struct sphere
{
    char id;
    int x, y, sphere_tile;
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
        int sphere_tile = SPHERE_TILES - i;
        spheres[i].id = SMS_addSprite(i * 10, i * 10, TEST_OFFSET + sphere_tile);
        spheres[i].x = i * 10;
        spheres[i].y = i * 10;
        spheres[i].sphere_tile = sphere_tile;
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
        SMS_updateSpriteImage(spheres[i].id, TEST_OFFSET + spheres[i].sphere_tile);

        if (++spheres[i].x > 256)
            spheres[i].x = 0;
        if (++spheres[i].y > 192)
            spheres[i].y = 0;
        if (scroll_x % 4 == 0 && --spheres[i].sphere_tile < 0)
            spheres[i].sphere_tile = SPHERE_TILES;
    }
}
