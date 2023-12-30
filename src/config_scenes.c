#include "config_scenes.h"
#include "scenes/city.h"
#include "scenes/default.h"
#include "scenes/eye.h"
#include "scenes/fire.h"
#include "scenes/logo.h"
#include "scenes/plasma.h"
#include "scenes/scroller.h"
#include "scenes/sineline.h"
#include "scenes/sphere.h"
#include "scenes/type.h"

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

    scenes[CITY].init = city_init;
    scenes[CITY].update = city_update;
    scenes[CITY].end = city_end;

    scenes[EYE].init = eye_init;
    scenes[EYE].update = eye_update;
    scenes[EYE].end = eye_end;

    scenes[FIRE].init = fire_init;
    scenes[FIRE].update = fire_update;
    scenes[FIRE].end = fire_end;

    scenes[LOGO].init = logo_init;
    scenes[LOGO].update = logo_update;
    scenes[LOGO].end = logo_end;

    scenes[PLASMA].init = plasma_init;
    scenes[PLASMA].update = plasma_update;
    scenes[PLASMA].end = plasma_end;

    scenes[SCROLLER].init = scroller_init;
    scenes[SCROLLER].update = scroller_update;
    scenes[SCROLLER].end = scroller_end;

    scenes[SINELINE].init = sineline_init;
    scenes[SINELINE].update = sineline_update;
    scenes[SINELINE].end = sineline_end;

    scenes[SPHERE].init = sphere_init;
    scenes[SPHERE].update = sphere_update;
    scenes[SPHERE].end = sphere_end;

    scenes[TYPE].init = type_init;
    scenes[TYPE].update = type_update;
    scenes[TYPE].end = type_end;
}
