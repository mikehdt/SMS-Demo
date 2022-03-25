ifeq ($(OS), Windows_NT)
	RM = del /f /q
	CP = copy /Y
	ifdef ComSpec
		SHELL := $(ComSpec)
	endif
	ifdef COMSPEC
		SHELL := $(COMSPEC)
	endif
else
	RM = rm -rf
	CP = cp -f
endif

CC = sdcc
IHX2SMS = ihx2sms

ROM = ./dist/sms-demo.sms
IHXFILE = ./dist/sms-demo.ihx

# Note: May need to consider -DPAL_MACHINE there if wanting to make an NTSC ver.
CFLAGS = --std-sdcc11 -c -mz80 --peep-file ./compile/smslib/peep-rules.txt --opt-code-speed -DPAL_MACHINE
LDFLAGS = -mz80 --no-std-crt0 --data-loc 0xC000 -Wl-b_BANK2=0x8000 -Wl-b_BANK3=0x8000

ASSETS = $(addprefix ./src/, assets2banks.h)
OBJS = $(addprefix ./compile/, smslib/crt0_sms.rel   main.rel   check_keys.rel init_console.rel init_scenes.rel palettes.rel update_scenes.rel   clear_tilemap.rel memcpy_expand_byte.rel ps_rand.rel screen_buffer.rel sintab.rel   default.rel fire.rel grid.rel intro.rel particles.rel plasma.rel scroller.rel sphere.rel sineline.rel type.rel)
BANKS = $(addprefix ./compile/, bank2.rel bank3.rel)
LIBS = SMSlib.lib

all: CFLAGS += --debug
all: LDFLAGS += --debug
all: build

dist: clean
dist: build

build: $(ROM)

$(ROM): $(IHXFILE)
	$(IHX2SMS) $(IHXFILE) $(ROM)

$(IHXFILE): $(OBJS)
	$(CC) -o $(IHXFILE) $(LDFLAGS) $(OBJS) $(LIBS) $(BANKS)

%.rel: ./src/%.c
	$(CC) -c $(CFLAGS) $<
%.rel: ./src/engine/%.c
	$(CC) -c $(CFLAGS) $<
%.rel: ./src/helpers/%.c
	$(CC) -c $(CFLAGS) $<
%.rel: ./src/scenes/%.c
	$(CC) -c $(CFLAGS) $<

# This isn't working yet on Windows
# clean:
# 	$(RM) $(ROM) $(addprefix ./compile/, *.sym *.lnk *.ihx *.map *.lst *.asm *.bin *.lk *.noi)

help:
	echo Usage:
	echo make          = builds all
