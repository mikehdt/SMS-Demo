@echo off

:: Note about -tileoffset -- it needs to come *before* -savetilemap, else it's ignored

:: Clean Assets
call .\scripts\clean-assets.bat

:: Build Assets
cd assets

:: Music
copy .\music\*.psg .\

:: Backgrounds
for %%f in (.\backgrounds\*.png) do ..\utils\bmp2tile\BMP2Tile.exe "%%f" -mirror -removedupes -palsms -savetiles "%%~nf.tiles.psgcompr" -savetilemap "%%~nf.tilemap.stmcompr" -savepalette "%%~nf.palette.bin"

:: Sprites (SMS can't flip sprites, so don't dedupe via mirroring)
for %%f in (.\sprites\*.png) do ..\utils\bmp2tile\BMP2Tile.exe "%%f" -removedupes -nomirror -palsms -savetiles "%%~nf.tiles.psgcompr" -savepalette "%%~nf.palette.bin"

:: Custom stuff for fussy images
..\utils\bmp2tile\BMP2Tile.exe .\backgrounds\custom\da_mini.png -palsms -savetiles "da_mini.tiles.psgcompr" -tileoffset 1 -savetilemap "da_mini.tilemap.stmcompr" -savepalette "da_mini.palette.bin"
..\utils\bmp2tile\BMP2Tile.exe .\custom\fire_grade.png -noremovedupes -palsms -savetiles "fire_grade.tiles.psgcompr" -savetilemap "fire_grade.tilemap.stmcompr" -savepalette "fire_grade.palette.bin"
..\utils\bmp2tile\BMP2Tile.exe .\custom\plasma_grade.png -noremovedupes -palsms -savetiles "plasma_grade.tiles.psgcompr" -savetilemap "plasma_grade.tilemap.stmcompr" -savepalette "plasma_grade.palette.bin"

:: Convert to ROM banks and move them to the compile folder for use
assets2banks . --firstbank=2 --singleheader --compile
move *.rel ..\compile

:: This header is needed for the source to build
move assets2banks.h ..\src

:: Tidy up
del *.bin > nul
del *.stmcompr > nul
del *.psgcompr > nul
del *.psg > nul

cd ..
