#include "sprites.h"
#include "../libs/SMSlib.h"

void clear_sprites(void)
{
    SMS_initSprites();

    for (int i = 0; i <= 64; i++)
    {
        SMS_hideSprite(i);
    }

    SMS_setSpriteMode(SPRITEMODE_NORMAL);
    SMS_copySpritestoSAT();
}
