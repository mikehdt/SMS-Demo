@echo off

:: Note about -tileoffset -- it needs to come *before* -savetiles and -savetilemap, else it's ignored (or can cause a crash)

:: Clean Assets
call .\scripts\clean-assets.bat

:: Build Assets
cd assets

:: Music
copy .\music\darkowl3_50.psg .\

:: Backgrounds with tilemap and palette
for %%f in (.\backgrounds\*.png) do ..\utils\bmp2tile\BMP2Tile.exe "%%f" -mirror -removedupes -palsms -savetiles "%%~nf.tiles.psgcompr" -savetilemap "%%~nf.tilemap.stmcompr" -savepalette "%%~nf.palette.bin"

:: Backgrounds without tilemap
for %%f in (.\backgrounds_nomap\*.png) do ..\utils\bmp2tile\BMP2Tile.exe "%%f" -nomirror -noremovedupes -palsms -savetiles "%%~nf.tiles.psgcompr" -savepalette "%%~nf.palette.bin"

:: Backgrounds without tilemap or palette
for %%f in (.\backgrounds_nomap_nopal\*.png) do ..\utils\bmp2tile\BMP2Tile.exe "%%f" -mirror -removedupes -palsms -savetiles "%%~nf.tiles.psgcompr"

:: Sprites (SMS can't flip sprites, so don't dedupe mirrored)
for %%f in (.\sprites\*.png) do ..\utils\bmp2tile\BMP2Tile.exe "%%f" -noremovedupes -nomirror -palsms -savetiles "%%~nf.tiles.psgcompr" -savepalette "%%~nf.palette.bin"

:: --- CUSTOM FUSSY ASSETS ---
:: DA Logo (offset 1)
..\utils\bmp2tile\BMP2Tile.exe .\custom\da_mini.png -noremovedupes -palsms -savetiles "da_mini.tiles.psgcompr" -tileoffset 1
:: Lady's Third Eye (offset 256)
..\utils\bmp2tile\BMP2Tile.exe .\custom\lady_eye.png -mirror -removedupes -palsms -savetiles "lady_eye.tiles.psgcompr" -tileoffset 256
:: Mini Lady (sprite palette)
..\utils\bmp2tile\BMP2Tile.exe .\custom\lady_mini.png -mirror -removedupes -palsms -spritepalette -savetiles "lady_mini.tiles.psgcompr" -savetilemap "lady_mini.tilemap.stmcompr" -savepalette "lady_mini.palette.bin"
:: Mini Lady Midriff (sprite palette)
..\utils\bmp2tile\BMP2Tile.exe .\custom\lady_mini_spr.png -nomirror -noremovedupes -palsms -spritepalette -savetiles "lady_mini_spr.tiles.psgcompr"
:: Mini Lady Eyes (sprite palette)
..\utils\bmp2tile\BMP2Tile.exe .\custom\lady_mini_eyes.png -nomirror -noremovedupes -palsms -spritepalette -savetiles "lady_mini_eyes.tiles.psgcompr"
:: Font
..\utils\bmp2tile\BMP2Tile.exe .\custom\font_beta.png -noremovedupes -nomirror -palsms -savetiles "font_beta.tiles.psgcompr" -savetilemap "font_beta.tilemap.stmcompr" -savepalette "font_beta.palette.bin"
:: Credits (palette only; tiles generated above)
..\utils\bmp2tile\BMP2Tile.exe .\backgrounds_nomap_nopal\credit_bananaboy.png -palsms -savepalette "credits.palette.bin"

:: Convert to ROM banks and move them to the compile folder for use
assets2banks . --firstbank=2 --singleheader --compile --allowsplitting
move *.rel ..\compile

:: This header is needed for the source to build
move assets2banks.h ..\src

:: Tidy up
del *.bin > nul
del *.stmcompr > nul
del *.psgcompr > nul
del *.psg > nul

cd ..
