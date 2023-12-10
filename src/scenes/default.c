#include "default.h"
#include "../config_scenes.h"
#include "../engine/scenes.h"

void default_init(void) {}

void default_update(void)
{
    // Hacky!
    // if (current_music_bank == 0)
    //     play_song();

    next_scene();
}

void default_end(void) {}
