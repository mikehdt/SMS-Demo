#ifndef __CONFIG_SCENES_H
#define __CONFIG_SCENES_H

enum SCENES
{
    DEFAULT = 0, // Scene counter; must be first
    LOGO_A,      // DA logo, plus credits
    CITY_A,      // Fade in art, pan
    LOGO_B,      // DA logo, plus credits
    LADY_A,      // Distant and then closeup of the lady
    CITY_B,      // Back to the city, sine-LUT eyes scatter, pan up to the sky
    EYE,         // Big spooky eye slides in time with prev scene; its iris fades out, sphere from next scene fades in place
    SPHERE,      // The sphere 'pops' from the eye, bounces around the screen for a bit with 8-way palette animation in sync with the movement, sphere slides or bounces off somewhere
    SINELINE,    // Line draws across the screen, eyes march across while lines spin around them in a sine wave-esque style
    FIRE,        // Last scene line comes to a rest, then fire bursts up (half screen or so for perf? Maybe scroll V to make it feel better)
    LADY_B,      // Cut back to lady, who looks more worried
    PLASMA,      // Eye from before has plasma in it now, then cut to full screen plasma if we want to tank performance lul
    LADY_C,      // Lady is now 'hypnotised', her third eye appears, turned into a skull (and her eyeballs fly off, MAYBE?)
    CITY_C,      // Eyes leave the city on fire, greets, fade out
    MAX_SCENES   // Scene counter; must be last
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
