#include "default.h"
#include "../config_scenes.h"
#include "../engine/audio.h"
#include "../engine/scenes.h"

void default_init(void) {}

void default_update(void)
{
    play_song();

    next_scene();
}

void default_end(void) {}
