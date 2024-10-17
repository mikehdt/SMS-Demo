#ifndef __CONFIG_SCENES_H
#define __CONFIG_SCENES_H

enum SCENES
{
    DEFAULT = 0, // Scene counter; must be first
    LOGO,        // DA logo
    CREDITS_A,   // Coding credit
    CITY_A,
    CREDITS_B, // Graphics credit
    CITY_B,
    CREDITS_C, // Music credit
    CITY_C,
    // EYE, // Big spooky eye slides in time with prev scene; its iris fades out, sphere from next scene fades in place
    // SPHERE, // The sphere 'pops' from the eye, bounces around the screen for a bit with 8-way palette animation in sync with the movement, sphere slides or bounces off somewhere
    // SINELINE, // Line draws across the screen, eyes march across while lines spin around them in a sine wave-esque style
    // FIRE,        // Last scene line comes to a rest, then fire bursts up (half screen or so for perf? Maybe scroll V to make it feel better)
    // PLASMA,      // Eye from before has plasma in it now, then cut to full screen plasma if we want to tank performance lul
    MAX_SCENES // Scene counter; must be last
};

typedef void (*ptr_func)(void);

typedef struct
{
    ptr_func init;
    ptr_func update;
    ptr_func end;
} Scenes;

extern Scenes scenes[MAX_SCENES];

void scenes_init(void);

#endif
