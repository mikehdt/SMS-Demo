@echo off

cd assets

:: Backgrounds
cd backgrounds
for %%f in (*.png) do ..\..\utils\bmp2tile\BMP2Tile.exe "%%f" -palsms -tileoffset 0 -savetiles "..\%%~nf.tiles.bin" -savetilemap "..\%%~nf.tilemap.bin" -savepalette "..\%%~nf.palette.bin"
cd ..
:: Sprites
:: Audio
:: for %%f in (music\*.vg*) do PSGTool "%%f"

cd ..\src\banks

assets2banks ..\..\assets

sdcc --debug -c -mz80 --opt-code-speed --std-c99 --constseg BANK2 bank2.c

:: Tidy up
del *.asm > nul
del *.lst > nul
del *.sym > nul
