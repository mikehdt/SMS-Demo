#include "fast_rand.h"

char fast_rand(void) __naked
{
    // clang-format off
__asm
    add hl, hl
    sbc a, a
    and #45
    xor l
    ld l, a
    ld a, r
    add a, h
    ld l, a; // move into l to return the result to C
    ret
__endasm;
    // clang-format on
}
