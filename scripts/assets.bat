@echo off

:: Note about -tileoffset -- it needs to come *before* -savetiles and -savetilemap, else it's ignored (or can cause a crash)

:: Clean Assets
call .\scripts\clean-assets.bat

:: Build Assets
cd assets

:: Music
copy .\music\*.psg .\

:: Backgrounds with tilemap and palette
for %%f in (.\backgrounds\*.png) do ..\utils\bmp2tile\BMP2Tile.exe "%%f" -mirror -removedupes -palsms -savetiles "%%~nf.tiles.psgcompr" -savetilemap "%%~nf.tilemap.stmcompr" -savepalette "%%~nf.palette.bin"

:: Backgrounds without tilemap
for %%f in (.\backgrounds_nomap\*.png) do ..\utils\bmp2tile\BMP2Tile.exe "%%f" -mirror -removedupes -palsms -savetiles "%%~nf.tiles.psgcompr" -savepalette "%%~nf.palette.bin"

:: Backgrounds without tilemap or palette
for %%f in (.\backgrounds_nomap_nopal\*.png) do ..\utils\bmp2tile\BMP2Tile.exe "%%f" -mirror -removedupes -palsms -savetiles "%%~nf.tiles.psgcompr"

:: Sprites (SMS can't flip sprites, so don't dedupe mirrored)
for %%f in (.\sprites\*.png) do ..\utils\bmp2tile\BMP2Tile.exe "%%f" -removedupes -nomirror -palsms -savetiles "%%~nf.tiles.psgcompr" -savepalette "%%~nf.palette.bin"

:: --- CUSTOM FUSSY ASSETS ---
:: DA Logo (offset 1)
..\utils\bmp2tile\BMP2Tile.exe .\custom\da_mini.png -noremovedupes -palsms -savetiles "da_mini.tiles.psgcompr" -tileoffset 1
:: Credits (palette only; tiles generated above)
..\utils\bmp2tile\BMP2Tile.exe .\backgrounds_nomap_nopal\credit_bananaboy.png -palsms -savepalette "credits.palette.bin"

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
