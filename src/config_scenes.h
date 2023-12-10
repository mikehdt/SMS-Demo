#ifndef __CONFIG_SCENES_H
#define __CONFIG_SCENES_H

enum SCENES
{
    DEFAULT = 0,
    SPHERE,
    PLASMA,
    LOGO,
    SCROLLER,
    FIRE,
    TYPE,
    MAX_SCENES // This creates a max counter for us, so long as it's last :)
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
