#include "ps_rand.h"
#include <stdint.h>

uint16_t RandomSeed = 0;

char ps_rand(void) __naked
{
    // Code adapted for SDCC from Phantasy Star's PRNG as documented at
    // https://www.smspower.org/Development/RandomNumberGenerator
    // clang-format off
    __asm
    GetRandomNumber:
        ld      hl, (_RandomSeed)
        ld      a, h        ; // get high byte
        rrca                ; // rotate right by 2
        rrca
        xor     h           ; // xor with original
        rrca                ; // rotate right by 1
        xor     l           ; // xor with low byte
        rrca                ; // rotate right by 4
        rrca
        rrca
        rrca
        xor     l           ; // xor again
        rra                 ; // rotate right by 1 through carry
        adc     hl, hl      ; // add RandomSeed to itself
        jr      nz, RandomContinue
        ld      hl, #0x733c ; // if last xor resulted in zero then reseed rng
    RandomContinue:
        ld      a, r        ; // r = refresh register = semi-random number
        xor     l           ; // xor with l which is fairly random
        ld      (_RandomSeed), hl
        ld      l, a        ; // move a into l to return a char back to the caller
        ret
    __endasm;
    // clang-format on
}
