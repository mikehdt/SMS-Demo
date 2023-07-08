#include "console_init.h"
#include "../engine/global_variables.h"
#include "../engine/palettes.h"
#include "../libs/SMSlib.h"
#include "sprites.h"
#include "tilemap.h"
#include <stdbool.h>

void console_init(void)
{
    current_scene = 0;
    current_scene_stage = 0;
    target_scene_stage = 0;

    current_rom_bank = 0;
    current_music_bank = 0;
    current_fx_bank = 0;

    // SMS_VDPturnOnFeature(VDPFEATURE_EXTRAHEIGHT); // PAL / SMS II only
    // SMS_VDPturnOnFeature(VDPFEATURE_240LINES);    // PAL / SMS II only

    init_sprites(SPRITEMODE_NORMAL, true);

    set_palette(palette_black, PALETTE_BOTH);
    load_blank_tile(0);
    clear_tilemap(0);

    SMS_displayOn();
}
