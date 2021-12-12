;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.1.0 #12072 (MINGW64)
;--------------------------------------------------------
	.module main
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl ___SMS__SDSC_signature
	.globl ___SMS__SDSC_descr
	.globl ___SMS__SDSC_name
	.globl ___SMS__SDSC_author
	.globl ___SMS__SEGA_signature
	.globl _main
	.globl _hello_world
	.globl _SMS_VRAMmemcpy
	.globl _SMS_loadBGPalette
	.globl _SMS_waitForVBlank
	.globl _SMS_VDPturnOnFeature
	.globl _SMS_SRAM
	.globl _SRAM_bank_to_be_mapped_on_slot2
	.globl _ROM_bank_to_be_mapped_on_slot2
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
G$ROM_bank_to_be_mapped_on_slot2$0_0$0 == 0xffff
_ROM_bank_to_be_mapped_on_slot2	=	0xffff
G$SRAM_bank_to_be_mapped_on_slot2$0_0$0 == 0xfffc
_SRAM_bank_to_be_mapped_on_slot2	=	0xfffc
G$SMS_SRAM$0_0$0 == 0x8000
_SMS_SRAM	=	0x8000
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
	G$hello_world$0$0	= .
	.globl	G$hello_world$0$0
	C$main.c$6$0_0$65	= .
	.globl	C$main.c$6$0_0$65
;main.c:6: void hello_world()
;	---------------------------------
; Function hello_world
; ---------------------------------
_hello_world::
	C$main.c$8$1_0$65	= .
	.globl	C$main.c$8$1_0$65
;main.c:8: SMS_loadTiles(test_tiles_bin, SPLASH_TILES, 8);
	ld	hl, #0x0008
	push	hl
	ld	hl, #_test_tiles_bin
	push	hl
	ld	hl, #0x4000
	push	hl
	call	_SMS_VRAMmemcpy
	C$main.c$9$1_0$65	= .
	.globl	C$main.c$9$1_0$65
;main.c:9: SMS_loadTileMap(0, 0, test_tilemap_bin, 8);
	ld	hl, #0x0008
	push	hl
	ld	hl, #_test_tilemap_bin
	push	hl
	ld	hl, #0x7800
	push	hl
	call	_SMS_VRAMmemcpy
	C$main.c$10$1_0$65	= .
	.globl	C$main.c$10$1_0$65
;main.c:10: SMS_loadBGPalette(test_palette_bin);
	ld	hl, #_test_palette_bin
	C$main.c$11$1_0$65	= .
	.globl	C$main.c$11$1_0$65
;main.c:11: }
	C$main.c$11$1_0$65	= .
	.globl	C$main.c$11$1_0$65
	XG$hello_world$0$0	= .
	.globl	XG$hello_world$0$0
	jp	_SMS_loadBGPalette
	G$main$0$0	= .
	.globl	G$main$0$0
	C$main.c$13$1_0$67	= .
	.globl	C$main.c$13$1_0$67
;main.c:13: void main(void)
;	---------------------------------
; Function main
; ---------------------------------
_main::
	C$main.c$15$1_0$67	= .
	.globl	C$main.c$15$1_0$67
;main.c:15: SMS_mapROMBank(2);
	ld	hl, #_ROM_bank_to_be_mapped_on_slot2
	ld	(hl), #0x02
	C$main.c$16$1_0$67	= .
	.globl	C$main.c$16$1_0$67
;main.c:16: hello_world();
	call	_hello_world
	C$main.c$17$1_0$67	= .
	.globl	C$main.c$17$1_0$67
;main.c:17: SMS_displayOn();
	ld	hl, #0x0140
	call	_SMS_VDPturnOnFeature
00102$:
	C$main.c$20$3_0$69	= .
	.globl	C$main.c$20$3_0$69
;main.c:20: SMS_waitForVBlank();
	call	_SMS_waitForVBlank
	C$main.c$22$2_0$67	= .
	.globl	C$main.c$22$2_0$67
;main.c:22: }
	C$main.c$22$2_0$67	= .
	.globl	C$main.c$22$2_0$67
	XG$main$0$0	= .
	.globl	XG$main$0$0
	jr	00102$
	.area _CODE
Fmain$__str_0$0_0$0 == .
__str_0:
	.ascii "Mike"
	.db 0x00
Fmain$__str_1$0_0$0 == .
__str_1:
	.ascii "Hello World"
	.db 0x00
Fmain$__str_2$0_0$0 == .
__str_2:
	.ascii "I have no idea what I'm doing"
	.db 0x00
	.area _INITIALIZER
	.area _CABS (ABS)
	.org 0x7FF0
G$__SMS__SEGA_signature$0_0$0 == .
___SMS__SEGA_signature:
	.db #0x54	; 84	'T'
	.db #0x4d	; 77	'M'
	.db #0x52	; 82	'R'
	.db #0x20	; 32
	.db #0x53	; 83	'S'
	.db #0x45	; 69	'E'
	.db #0x47	; 71	'G'
	.db #0x41	; 65	'A'
	.db #0xff	; 255
	.db #0xff	; 255
	.db #0xff	; 255
	.db #0xff	; 255
	.db #0x99	; 153
	.db #0x99	; 153
	.db #0x00	; 0
	.db #0x4c	; 76	'L'
	.org 0x7FDB
G$__SMS__SDSC_author$0_0$0 == .
___SMS__SDSC_author:
	.ascii "Mike"
	.db 0x00
	.org 0x7FCF
G$__SMS__SDSC_name$0_0$0 == .
___SMS__SDSC_name:
	.ascii "Hello World"
	.db 0x00
	.org 0x7FB1
G$__SMS__SDSC_descr$0_0$0 == .
___SMS__SDSC_descr:
	.ascii "I have no idea what I'm doing"
	.db 0x00
	.org 0x7FE0
G$__SMS__SDSC_signature$0_0$0 == .
___SMS__SDSC_signature:
	.db #0x53	; 83	'S'
	.db #0x44	; 68	'D'
	.db #0x53	; 83	'S'
	.db #0x43	; 67	'C'
	.db #0x01	; 1
	.db #0x00	; 0
	.db #0x12	; 18
	.db #0x12	; 18
	.db #0x21	; 33
	.db #0x20	; 32
	.db #0xdb	; 219
	.db #0x7f	; 127
	.db #0xcf	; 207
	.db #0x7f	; 127
	.db #0xb1	; 177
	.db #0x7f	; 127
