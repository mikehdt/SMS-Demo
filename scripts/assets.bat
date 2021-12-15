@echo off

:: Clean Assets
call .\scripts\clean.bat

:: Build Assets
cd assets

:: Backgrounds
for %%f in (.\backgrounds\*.png) do ..\utils\bmp2tile\BMP2Tile.exe "%%f" -mirror -removedupes -palsms -savetiles "%%~nf.tiles.psgcompr" -savetilemap "%%~nf.tilemap.stmcompr" -savepalette "%%~nf.palette.bin"

:: Convert to ROM banks
cd ..\compile
assets2banks ..\assets --singleheader --compile

:: This header is needed for the source to build
move assets2banks.h ..\src

cd ..
