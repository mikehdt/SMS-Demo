#include "memcpy_expand_byte.h"

#pragma save
#pragma disable_warning 85
void VRAMmemcpyExpandByte(unsigned int dst, const void *src, unsigned int size) __naked __z88dk_callee __preserves_regs(iyh, iyl)
{
    // Written by @bananaboy
    // dst in hl
    // src in de
    // size onto the stack
    // handwritten asm code
    // clang-format off
    __asm
        set 6,h
        rst #0x08

        ex de, hl          ; move src to hl

        pop de             ; pop ret address
        pop bc             ; pop size
        push de            ; push ret address

        dec bc
        inc b
        inc c              ; increment B if C is not zero

        ld a, b            ; HI(size)
        ld b, c            ; LO(size)

        ld c, #0xbe
        ld d, #0           ; 7

    1$:
        outi               ; 16
        jr 2$              ; 10
    2$:
        nop                ; 4 - in theory this should not be needed, but without an extra delay I get corruption.
        out (c), d         ; 12
        nop                ; 4
        jp  nz, 1$         ; 10 = 26 (VRAM safe)
        dec a
        jp  nz, 1$
        ret                ; because this function is naked
    __endasm;
    // clang-format on
}
#pragma restore
