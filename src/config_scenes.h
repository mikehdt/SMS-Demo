#ifndef __CONFIG_SCENES_H
#define __CONFIG_SCENES_H

enum SCENES
{
    DEFAULT = 0, // Scene counter; must be first
    SINELINE,

    // ---
    LOGO,
    CREDITS_A, // Credits I: Coding
    CITY_A,    // Fade I
    CREDITS_B, // Credits II: Graphics
    CITY_B,    // Fade II
    CREDITS_C, // Credits III: Music
    CITY_C,    // Fade III + eye particles
    EYE,
    // SINELINE,
    // FIRE,
    // LADY,
    // PLASMA,
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
