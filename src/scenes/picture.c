#include "picture.h"
#include "../assets2banks.h" // Generated with the assets task
#include "../engine/core.h"
#include "../engine/palettes.h"
#include "../libs/SMSlib.h"

#define PALMS_OFFSET 57
#define NUM_SPHERES 7
#define SPHERE_TILES 6 // 0-offset to save a -1 later

unsigned int scroll_x;

struct sphere
{
    char id;
    int x, y, sphere_tile;
};

struct sphere spheres[NUM_SPHERES];

void init_spheres(void)
{
    int i = 0;

    SMS_loadPSGaidencompressedTiles(spheres_tiles_psgcompr, PALMS_OFFSET);
    SMS_loadSpritePalette(palms_palette_bin);
    SMS_initSprites();

    for (i = 0; i < NUM_SPHERES; i++)
    {
        int sphere_tile = SPHERE_TILES - i;
        spheres[i].id = SMS_addSprite(i * 10, i * 10, PALMS_OFFSET + sphere_tile);
        spheres[i].x = i * 10;
        spheres[i].y = i * 10;
        spheres[i].sphere_tile = sphere_tile;
        // If the return is -1, no more sprites could be allocated
        // If the return is -2, the y-coordinate is invalid
    }
}

void animate_spheres(void)
{
    unsigned int i;

    for (i = 0; i < NUM_SPHERES; i++)
    {
        SMS_updateSpritePosition(spheres[i].id, spheres[i].x, spheres[i].y);
        SMS_updateSpriteImage(spheres[i].id, PALMS_OFFSET + spheres[i].sphere_tile);

        if (++spheres[i].x > 256)
            spheres[i].x = 0;
        if (++spheres[i].y > 192)
            spheres[i].y = -8; // hmm...
        if (scroll_x % 4 == 0 && --spheres[i].sphere_tile < 0)
            spheres[i].sphere_tile = SPHERE_TILES;
    }
}

void picture_scene_init(void)
{
    SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK); // Hide stuff for scrolling
    SMS_setBGScrollX(0);

    palette_set_black(PALETTE_BACKGROUND);
    SMS_loadPSGaidencompressedTiles(palms_tiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(0, 0, palms_tilemap_stmcompr);
    fade_to_palette(palms_palette_bin, 16, 6);
    // fade_from_black(palms_palette_bin);

    scroll_x = 0;

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
    uint8_t palette_black[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    SMS_initSprites();
    fade_to_palette(palette_black, 16, 6);

    SMS_setBGScrollX(0);
    SMS_VDPturnOffFeature(VDPFEATURE_LEFTCOLBLANK); // Hide stuff for scrolling
}
