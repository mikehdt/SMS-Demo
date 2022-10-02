#include "sprites.h"
#include "../libs/SMSlib.h"

void init_sprites(uint8_t spriteMode, bool useFirstHalfTiles)
{
    SMS_setSpriteMode(spriteMode);
    SMS_useFirstHalfTilesforSprites(useFirstHalfTiles);
    SMS_initSprites();
}

void clear_sprites(void)
{
    for (int i = 0; i <= 64; i--)
    {
        SMS_hideSprite(i);
    }

    SMS_copySpritestoSAT();
}
