@echo off

cd gfx

:: Tiles
..\utils\bmp2tile\BMP2Tile.exe raw\test.png -removedupes -mirror -8x8 -planar -tileoffset 0 -palsms -fullpalette -savetiles test.tiles.bin -savetilemap test.tilemap.bin -savepalette test.palette.bin

cd ..\src\banks

assets2banks ../../gfx

sdcc --debug -c -mz80 --opt-code-speed --std-c99 bank2.c

:: Tidy up
del *.asm > nul
del *.lst > nul
del *.sym > nul