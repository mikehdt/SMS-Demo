#include "fast_rand.h"

char fast_rand(void) __naked
{
    // clang-format off
__asm
    ;add de, de
    ;sbc a, a
    ;and #45
    ;xor e
    ;ld e, a
    ;ld a, r
    ;add a, d
    ;ld e, a; // move into e to return the result to C
    ret
__endasm;
    // clang-format on
}
