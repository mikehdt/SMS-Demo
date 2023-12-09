#include "screen_buffer.h"
#include <string.h>

uint8_t screen_buffer[SCREEN_SIZE_MAX] = {0x00};

void clear_screen_buffer(void)
{
    memset(screen_buffer, 0x00, sizeof screen_buffer);
}
