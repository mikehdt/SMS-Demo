#ifndef __SCENES_H
#define __SCENES_H

typedef void (*ptr_func)(void);

typedef struct
{
    ptr_func init;
    ptr_func update;
    ptr_func end;
} Scenes;

enum SCENES
{
    SCENE_DEFAULT = 0,
    SCENE_FIRE,
    SCENE_INTRO,
    SCENE_PARTICLES,
    SCENE_PLASMA,
    SCENE_SCROLLER,
    SCENE_SINELINE,
    SCENE_SPHERE,
    SCENE_TYPE,
    MAX_SCENES // This creates a max counter for us, so long as it's last :)
};

extern Scenes scenes[MAX_SCENES];

void scenes_init(void);

#endif
