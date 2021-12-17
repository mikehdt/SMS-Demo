@echo off

:: Clean Assets
call .\scripts\clean.bat

:: Build Assets
cd assets

:: Backgrounds
for %%f in (.\backgrounds\*.png) do ..\utils\bmp2tile\BMP2Tile.exe "%%f" -mirror -removedupes -palsms -savetiles "%%~nf.tiles.psgcompr" -savetilemap "%%~nf.tilemap.stmcompr" -savepalette "%%~nf.palette.bin"

:: Sprites
for %%f in (.\sprites\*.png) do ..\utils\bmp2tile\BMP2Tile.exe "%%f" -removedupes -palsms -savetiles "%%~nf.tiles.psgcompr"

:: Convert to ROM banks and move them to the compile folder for use
assets2banks . --singleheader --compile
move *.rel ..\compile

:: This header is needed for the source to build
move assets2banks.h ..\src

:: Tidy up
del *.bin > nul
del *.stmcompr > nul
del *.psgcompr > nul

cd ..
