#include "fire.h"
#include "../assets2banks.h"
#include "../engine/core.h"
#include "../engine/palettes.h"
#include "../engine/scenes.h"
#include "../libs/SMSlib.h"
#include <stdlib.h>

// #define MAX(a, b) ((a) > (b)) ? (a) : (b); // Best a/b are not expressions...

// const uint16_t screen_size = SCREEN_COLUMNS * 24;
// const uint16_t offscreen_size = SCREEN_COLUMNS * 26;

#define ROW_WIDTH 32
#define ROW_TOTAL 1 // 24
#define FIRE_SIZE (ROW_TOTAL * ROW_WIDTH * 2)
#define SEED_SIZE ((ROW_TOTAL + 2) * ROW_WIDTH * 2)
uint16_t fire_idx, test;
uint8_t SEED = 0;
uint16_t RandomSeed = 0;

// Compensate for 8-bit width by multiplying by 2
int8_t fire[ROW_WIDTH * (ROW_TOTAL + 2) * 2] = {0};

void fire_scene_init(void)
{
    SMS_loadPSGaidencompressedTiles(fire_grade_tiles_psgcompr, 0);
    SMS_loadBGPalette(fire_grade_palette_bin);
    SMS_loadSpritePalette(palette_black);

    clear_tilemap(0 | TILE_USE_SPRITE_PALETTE);
}

// Candidate to move to its own utility file
char ps_rand() __naked
{
    // Code adapted for SDCC from Phantasy Star's PRNG as documented at
    // https://www.smspower.org/Development/RandomNumberGenerator
    // clang-format off
__asm
GetRandomNumber:
    ld      hl, (_RandomSeed)
    ld      a, h        ; get high byte
    rrca                ; rotate right by 2
    rrca
    xor     h           ; xor with original
    rrca                ; rotate right by 1
    xor     l           ; xor with low byte
    rrca                ; rotate right by 4
    rrca
    rrca
    rrca
    xor     l           ; xor again
    rra                 ; rotate right by 1 through carry
    adc     hl, hl      ; add RandomNumberGeneratorWord to itself
    jr      nz, RandContinue
    ld      hl, #0x733c ; if last xor resulted in zero then reseed rng
RandContinue:
    ld      a, r        ; r = refresh register = semi-random number
    xor     l           ; xor with l which is fairly random
    ld      (_RandomSeed), hl
    ld      l, a        ; move a into l to return a char back to the caller
ret
__endasm;
    // clang-format on
}

char calc_cur_fire(void) __naked
{
    // This calculation _does_ cause int wrap-around, but would need a fast
    // way to counter this without an if condition...
    // clang-format off
__asm
    ld	bc, #_fire+0        ; load the address of the array in memory?

	ld	hl, (_fire_idx)     ; get the current array index
	ld	e, #0x3e            ; gonna read current index + 63 (one row minus one)
	add	hl, de              ; add the offset
	add	hl, bc              ; now add the array location in memory?
	ld	a, (hl)             ; read out the value from this compound memory location into a?
    ;	ld	-2 (ix), a          ; no idea what this is doing...
    ;	rla                     ; rotate the accumulator left (* 2)
    ;	sbc	a, a                ; subtract with carry a from itself? wut
    ;	ld	-1 (ix), a
	ld	hl, (_fire_idx)
	ld	e, #0x40            ; current index + 64
	add	hl, de              ; add the offset
	add	hl, bc              ; now add the array location in memory?
    add a, (hl)             ; add the memory at address (hl) to register a
    ;  	push	af              ; why?
    ;	rla
    ;	sbc	a, a
    ;	ld	e, a
    ;	pop	af
    ;	add	a, -2 (ix)
    ;	ld	-4 (ix), a
    ;	ld	a, e
    ;	adc	a, -1 (ix)
    ;	ld	-3 (ix), a          ; no seriously why
	ld	hl, (_fire_idx)
	ld	e, #0x42         ; current index + 65
	add	hl, de
	add	hl, bc
	add	a, (hl)
    ;	push	af
    ;	rla
    ;	sbc	a, a
    ;	ld	e, a
    ;	pop	af
    ;	add	a, -4 (ix)
    ;	ld	-2 (ix), a
    ;	ld	a, e
    ;	adc	a, -3 (ix)
    ;	ld	-1 (ix), a
	ld	hl, (_fire_idx)
	ld	e, #0x44
	add	hl, de
	add	hl, bc
	add	a, (hl)
	// ld	e, a
	// rla
	// sbc	a, a
	// ld	d, a
	// ld	l, -2 (ix)
	// ld	h, -1 (ix)
	// add	hl, de
	// ex	de,hl
	// sra	d
	// rr	e
	// sra	d
	// rr	e

    ld l, a
    ret
__endasm;
    // clang-format on
}

void fire_scene_update(void)
{
    uint8_t cur_fire;

    fire_idx = FIRE_SIZE;

    // Generate noise across "virtual" lines
    while (fire_idx < SEED_SIZE)
    {
        // This is messy, just ignore it for now :3
        fire[fire_idx] = ps_rand();
        fire_idx += 2; // Skip every second byte lulz
    }

    //   i   <- Current row item
    // a b c <- First row below
    //   x   <- Second row below
    fire_idx = 0;

    while (fire_idx < FIRE_SIZE)
    {
        cur_fire = calc_cur_fire();

        // cur_fire = ((fire[fire_idx + aVal] + fire[fire_idx + bVal] + fire[fire_idx + cVal] + fire[fire_idx + xVal]) >> 2);

        // if (cur_fire >= 4)
        //     cur_fire -= 4;

        fire[fire_idx] = cur_fire;

        fire_idx += 2; // Skip every second byte lulz
    }

    wait_for_vblank();

    // Dump the tilemap to the VDP - use offscreen_size for debug
    // SMS_VRAMmemcpy(SMS_PNTAddress, &fire, screen_size * 2); // 2 bytes per ea
    SMS_loadTileMapArea(0, 0, fire, ROW_WIDTH, ROW_TOTAL + 2);
}
