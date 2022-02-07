#include "clear_tilemap.h"
#include "../engine/globals.h"
#include "../libs/SMSlib.h"

void clear_tilemap(uint16_t tile) // Must be 16-bit, or else sad VDP
{
    // From sverx, a more efficient method
    SMS_VRAMmemsetW(XYtoADDR(0, 0), tile, (SCREEN_ROWS * SCREEN_COLUMNS * 2));
}
