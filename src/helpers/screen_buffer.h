#ifndef _SCREEN_BUFFER_H
#define _SCREEN_BUFFER_H
#include "../engine/global_constants.h"
#include <stdint.h>

extern uint8_t screen_buffer[SCREEN_SIZE_MAX];

void clear_screen_buffer(void);

#endif
