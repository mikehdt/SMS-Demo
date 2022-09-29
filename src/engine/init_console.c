#include "init_console.h"
#include "../engine/palettes.h"
#include "../libs/SMSlib.h"
#include "tilemap.h"
#include <stdbool.h>

void init_console(void)
{
    // SMS_VDPturnOnFeature(VDPFEATURE_EXTRAHEIGHT); // PAL / SMS II only
    // SMS_VDPturnOnFeature(VDPFEATURE_240LINES);    // PAL / SMS II only
    init_sprites(SPRITEMODE_NORMAL, true);
    // clear_sprites();

    set_palette(palette_black, PALETTE_BOTH);
    load_blank_tile(0);
    clear_tilemap(0);

    SMS_displayOn();
}
