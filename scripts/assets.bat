@echo off

:: Clean Assets
call .\scripts\clean.bat

:: Build Assets
cd assets

:: Backgrounds
for %%f in (.\backgrounds\*.png) do ..\utils\bmp2tile\BMP2Tile.exe "%%f" -mirror -removedupes -palsms -savetiles "%%~nf.tiles.psgcompr" -savetilemap "%%~nf.tilemap.stmcompr" -savepalette "%%~nf.palette.bin"

:: Sprites (SMS can't flip sprites, so don't dedupe via mirroring)
for %%f in (.\sprites\*.png) do ..\utils\bmp2tile\BMP2Tile.exe "%%f" -removedupes -nomirror -palsms -savetiles "%%~nf.tiles.psgcompr" -savepalette "%%~nf.palette.bin"

:: Custom stuff for fussy images
..\utils\bmp2tile\BMP2Tile.exe .\custom\noise_grade.png -noremovedupes -palsms -savetiles "noise_grade.tiles.psgcompr" -savetilemap "noise_grade.tilemap.stmcompr" -savepalette "noise_grade.palette.bin"

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
