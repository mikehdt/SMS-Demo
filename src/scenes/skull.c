#include "../assets2banks.h"
#include "../engine/palettes.h"
#include "../engine/scenes.h"
#include "../engine/tilemap.h"
#include "../libs/SMSlib.h"
#include "lady.h"

void skull_init(void)
{
    cur_stage = 1;

    SMS_waitForVBlank();
    load_palette(palette_black, PALETTE_BACKGROUND);

    clear_tilemap(0);
    SMS_mapROMBank(lady_palette_bin_bank);
    SMS_loadBGPalette(palette_black);
    SMS_loadPSGaidencompressedTiles(lady_tiles_psgcompr, 0);
    SMS_loadPSGaidencompressedTiles(lady_eye_tiles_psgcompr, 256);
    SMS_loadPSGaidencompressedTiles(lady_eyes_tiles_psgcompr, 264);
    SMS_loadPSGaidencompressedTiles(lady_lips_tiles_psgcompr, 284);
    SMS_loadSTMcompressedTileMap(6, 0, lady_tilemap_stmcompr);
}

void skull_update(void)
{
    uint8_t i;

    if (cur_stage == 1)
    {
        for (i = 0; i < 10; i++)
        {
            fade_from_black(lady_palette_bin, i);

            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
        }

        cur_stage = 2;
    }

    SMS_waitForVBlank();

    if (cur_frame > 80 && cur_stage == 2)
    {
        for (i = 0; i < 3; i++)
        {
            load_palette(palette_white, PALETTE_BACKGROUND);

            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();

            if (i == 0)
            {
                // Lips
                SMS_setTileatXY(13, 16, 284);
                SMS_setTileatXY(14, 16, 285);
                SMS_setTileatXY(15, 16, 286);
                SMS_setTileatXY(13, 17, 287);
                SMS_setTileatXY(14, 17, 288);
                SMS_setTileatXY(15, 17, 289);
                SMS_setTileatXY(13, 18, 290);
                SMS_setTileatXY(14, 18, 291);
                SMS_setTileatXY(15, 18, 292);
                SMS_setTileatXY(13, 19, 293);
                SMS_setTileatXY(14, 19, 294);
                SMS_setTileatXY(15, 19, 295);
                SMS_setTileatXY(18, 16, 284 | TILE_FLIPPED_X);
                SMS_setTileatXY(17, 16, 285 | TILE_FLIPPED_X);
                SMS_setTileatXY(16, 16, 286 | TILE_FLIPPED_X);
                SMS_setTileatXY(18, 17, 287 | TILE_FLIPPED_X);
                SMS_setTileatXY(17, 17, 288 | TILE_FLIPPED_X);
                SMS_setTileatXY(16, 17, 289 | TILE_FLIPPED_X);
                SMS_setTileatXY(18, 18, 290 | TILE_FLIPPED_X);
                SMS_setTileatXY(17, 18, 291 | TILE_FLIPPED_X);
                SMS_setTileatXY(16, 18, 292 | TILE_FLIPPED_X);
                SMS_setTileatXY(18, 19, 293 | TILE_FLIPPED_X);
                SMS_setTileatXY(17, 19, 294 | TILE_FLIPPED_X);
                SMS_setTileatXY(16, 19, 295 | TILE_FLIPPED_X);
            }
            else if (i == 1)
            {
                // Third Eye
                SMS_setTileatXY(14, 6, 256);
                SMS_setTileatXY(15, 6, 257);
                SMS_setTileatXY(14, 7, 258);
                SMS_setTileatXY(15, 7, 259);
                SMS_setTileatXY(14, 8, 260);
                SMS_setTileatXY(15, 8, 261);
                SMS_setTileatXY(14, 9, 262);
                SMS_setTileatXY(15, 9, 263);
                SMS_setTileatXY(16, 6, 257 | TILE_FLIPPED_X);
                SMS_setTileatXY(17, 6, 256 | TILE_FLIPPED_X);
                SMS_setTileatXY(16, 7, 259 | TILE_FLIPPED_X);
                SMS_setTileatXY(17, 7, 258 | TILE_FLIPPED_X);
                SMS_setTileatXY(16, 8, 261 | TILE_FLIPPED_X);
                SMS_setTileatXY(17, 8, 260 | TILE_FLIPPED_X);
                SMS_setTileatXY(16, 9, 263 | TILE_FLIPPED_X);
                SMS_setTileatXY(17, 9, 262 | TILE_FLIPPED_X);
            }
            else if (i == 2)
            {
                // Eyes
                SMS_setTileatXY(11, 9, 264);
                SMS_setTileatXY(12, 9, 265);
                SMS_setTileatXY(13, 9, 266);
                SMS_setTileatXY(11, 10, 269);
                SMS_setTileatXY(12, 10, 270);
                SMS_setTileatXY(13, 10, 271);
                SMS_setTileatXY(14, 10, 272);
                SMS_setTileatXY(11, 11, 274);
                SMS_setTileatXY(12, 11, 275);
                SMS_setTileatXY(13, 11, 276);
                SMS_setTileatXY(14, 11, 277);
                SMS_setTileatXY(11, 12, 279);
                SMS_setTileatXY(12, 12, 280);
                SMS_setTileatXY(13, 12, 281);
                SMS_setTileatXY(14, 12, 282);
                SMS_setTileatXY(20, 9, 264 | TILE_FLIPPED_X);
                SMS_setTileatXY(19, 9, 265 | TILE_FLIPPED_X);
                SMS_setTileatXY(18, 9, 266 | TILE_FLIPPED_X);
                SMS_setTileatXY(20, 10, 269 | TILE_FLIPPED_X);
                SMS_setTileatXY(19, 10, 270 | TILE_FLIPPED_X);
                SMS_setTileatXY(18, 10, 271 | TILE_FLIPPED_X);
                SMS_setTileatXY(17, 10, 272 | TILE_FLIPPED_X);
                SMS_setTileatXY(20, 11, 274 | TILE_FLIPPED_X);
                SMS_setTileatXY(19, 11, 275 | TILE_FLIPPED_X);
                SMS_setTileatXY(18, 11, 276 | TILE_FLIPPED_X);
                SMS_setTileatXY(17, 11, 277 | TILE_FLIPPED_X);
                SMS_setTileatXY(20, 12, 279 | TILE_FLIPPED_X);
                SMS_setTileatXY(19, 12, 280 | TILE_FLIPPED_X);
                SMS_setTileatXY(18, 12, 281 | TILE_FLIPPED_X);
                SMS_setTileatXY(17, 12, 282 | TILE_FLIPPED_X);
            }

            load_palette(lady_palette_bin, PALETTE_BACKGROUND);

            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
        }

        cur_stage = 3;
    }

    // cur_frame++;
    if (cur_frame++ > 160)
    {
        for (i = 0; i < 10; i++)
        {
            fade_to_black(lady_palette_bin, i);

            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
            SMS_waitForVBlank();
        }

        next_scene();
    }
}

void skull_end(void)
{
    SMS_waitForVBlank();
}
