;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.1.12 #12748 (MINGW64)
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
_ROM_bank_to_be_mapped_on_slot2	=	0xffff
_SRAM_bank_to_be_mapped_on_slot2	=	0xfffc
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
;main.c:6: void hello_world()
;	---------------------------------
; Function hello_world
; ---------------------------------
_hello_world::
;main.c:8: SMS_loadTiles(test_tiles_bin, SPLASH_TILES, 8);
	ld	hl, #0x0008
	push	hl
	ld	de, #_test_tiles_bin
	ld	hl, #0x4000
	call	_SMS_VRAMmemcpy
;main.c:9: SMS_loadTileMap(0, 0, test_tilemap_bin, 8);
	ld	hl, #0x0008
	push	hl
	ld	de, #_test_tilemap_bin
	ld	hl, #0x7800
	call	_SMS_VRAMmemcpy
;main.c:10: SMS_loadBGPalette(test_palette_bin);
	ld	hl, #_test_palette_bin
;main.c:11: }
	jp	_SMS_loadBGPalette
;main.c:12: void main (void)
;	---------------------------------
; Function main
; ---------------------------------
_main::
;main.c:14: hello_world();
	call	_hello_world
;main.c:15: SMS_displayOn();
	ld	hl, #0x0140
	call	_SMS_VDPturnOnFeature
00102$:
;main.c:18: SMS_waitForVBlank();
	call	_SMS_waitForVBlank
;main.c:20: }
	jr	00102$
	.area _CODE
__str_0:
	.ascii "Disasterarea"
	.db 0x00
__str_1:
	.ascii "Hello World"
	.db 0x00
__str_2:
	.ascii "I have no idea what I'm doing"
	.db 0x00
	.area _INITIALIZER
	.area _CABS (ABS)
	.org 0x7FF0
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
	.org 0x7FD3
___SMS__SDSC_author:
	.ascii "Disasterarea"
	.db 0x00
	.org 0x7FC7
___SMS__SDSC_name:
	.ascii "Hello World"
	.db 0x00
	.org 0x7FA9
___SMS__SDSC_descr:
	.ascii "I have no idea what I'm doing"
	.db 0x00
	.org 0x7FE0
___SMS__SDSC_signature:
	.db #0x53	; 83	'S'
	.db #0x44	; 68	'D'
	.db #0x53	; 83	'S'
	.db #0x43	; 67	'C'
	.db #0x01	; 1
	.db #0x00	; 0
	.db #0x15	; 21
	.db #0x09	; 9
	.db #0x17	; 23
	.db #0x20	; 32
	.db #0xd3	; 211
	.db #0x7f	; 127
	.db #0xc7	; 199
	.db #0x7f	; 127
	.db #0xa9	; 169
	.db #0x7f	; 127
