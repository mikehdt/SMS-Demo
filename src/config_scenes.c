#include "config_scenes.h"
#include "scenes/city.h"
#include "scenes/default.h"
#include "scenes/eye.h"
#include "scenes/fire.h"
#include "scenes/lady.h"
#include "scenes/lady_dist.h"
#include "scenes/logo.h"
#include "scenes/plasma.h"
#include "scenes/sineline.h"
#include "scenes/sphere.h"

Scenes scenes[MAX_SCENES];

void empty_fn(void) {}

// Idea: can I use a struct that's defined by the effects themselves to simplify this?
// IMPORTANT: All scenes must implement an init, update and end function.
void scenes_init(void)
{
    // Default
    scenes[DEFAULT].init = empty_fn;
    scenes[DEFAULT].update = default_update;
    scenes[DEFAULT].end = empty_fn;

    scenes[CITY_A].init = city_init;
    scenes[CITY_A].update = city_update;
    scenes[CITY_A].end = city_end;

    scenes[CITY_B].init = city_init;
    scenes[CITY_B].update = city_update;
    scenes[CITY_B].end = city_end;

    scenes[CITY_C].init = city_init;
    scenes[CITY_C].update = city_update;
    scenes[CITY_C].end = city_end;

    scenes[EYE].init = eye_init;
    scenes[EYE].update = eye_update;
    scenes[EYE].end = eye_end;

    scenes[FIRE].init = fire_init;
    scenes[FIRE].update = fire_update;
    scenes[FIRE].end = fire_end;

    scenes[LADY_A].init = lady_dist_init;
    scenes[LADY_A].update = lady_dist_update;
    scenes[LADY_A].end = lady_dist_end;

    scenes[LADY_B].init = lady_init;
    scenes[LADY_B].update = lady_update;
    scenes[LADY_B].end = lady_end;

    scenes[LADY_C].init = lady_init;
    scenes[LADY_C].update = lady_update;
    scenes[LADY_C].end = lady_end;

    scenes[LOGO].init = logo_init;
    scenes[LOGO].update = logo_update;
    scenes[LOGO].end = logo_end;

    scenes[PLASMA].init = plasma_init;
    scenes[PLASMA].update = plasma_update;
    scenes[PLASMA].end = plasma_end;

    scenes[SINELINE].init = sineline_init;
    scenes[SINELINE].update = sineline_update;
    scenes[SINELINE].end = sineline_end;

    scenes[SPHERE].init = sphere_init;
    scenes[SPHERE].update = sphere_update;
    scenes[SPHERE].end = sphere_end;
}
