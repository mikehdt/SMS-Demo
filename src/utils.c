#include "utils.h"
#include "libs/SMSlib.h"
#include <stdlib.h>

unsigned char fade_palette[FADE_STEPS][16];

void wait_for_frame(void)
{
    SMS_waitForVBlank();
    SMS_copySpritestoSAT(); // Update any sprite shenanigans
}

void clear_tilemap(uint8_t tile)
{
    // From sverx, a more efficient method
    SMS_VRAMmemsetW(XYtoADDR(0, 0), tile, SCREEN_ROWS * SCREEN_COLUMNS * 2);
}

#define getRFromRGB(color) color & 3        // 0000RR -- 0000RR
#define getGFromRGB(color) (color >> 2) & 3 // 00GG00 >> 0000GG
#define getBFromRGB(color) (color >> 4) & 3 // BB0000 >> 0000BB
#define setRToRGB(color) color & 3          // 0000RR -- 0000RR
#define setGToRGB(color) (color & 3) << 2   // 0000GG << 00GG00
#define setBToRGB(color) (color & 3) << 4   // 0000BB << BB0000

// To deal with later...
unsigned char cur_palette[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void palette_make_fade(unsigned char *new_palette)
{
    // Generate fade lookup ... not sure this is working properly yet
    for (uint8_t i = 0; i < FADE_STEPS; i++)
    {
        for (uint8_t j = 0; j < 16; j++)
        {
            unsigned char r, g, b;
            uint16_t progress_ratio = (i + 1) * 256 / FADE_STEPS;

            r = setRToRGB(getRFromRGB(new_palette[j]) * progress_ratio / 256);
            g = setGToRGB(getGFromRGB(new_palette[j]) * progress_ratio / 256);
            b = setBToRGB(getBFromRGB(new_palette[j]) * progress_ratio / 256);

            fade_palette[i][j] = r | g | b;
        }
    }
}

void palette_set(const void *palette, uint8_t paletteType)
{
    // Background palette
    if (paletteType == PALETTE_BOTH || paletteType == PALETTE_BACKGROUND)
        SMS_loadBGPalette(palette);

    // Sprite palette
    if (paletteType == PALETTE_BOTH || paletteType == PALETTE_SPRITE)
        SMS_loadSpritePalette(palette);
}

void palette_fadein_handler(uint8_t paletteType)
{
    uint8_t fadeSteps = 0;

    do
    {
        palette_set(fade_palette[fadeSteps], paletteType);
        wait_for_frame();
    } while (++fadeSteps < FADE_STEPS);
}

void palette_set_white(uint8_t paletteType)
{
    uint8_t palette_white[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    palette_set(palette_white, paletteType);
}

void palette_set_black(uint8_t paletteType)
{
    uint8_t palette_black[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    palette_set(palette_black, paletteType);
}
