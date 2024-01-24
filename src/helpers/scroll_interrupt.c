#include "../libs/SMSlib.h"

void set_scroll(unsigned int lineCount, void (*scrollHandler)(void))
{
    SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK);
    // SMS_setBGScrollX(0);
    SMS_setLineCounter(lineCount); // Every n + 1 scanlines (0 indexed)
    SMS_setLineInterruptHandler(scrollHandler);
    SMS_enableLineInterrupt();
}

void clear_scroll(void)
{
    SMS_VDPturnOffFeature(VDPFEATURE_LEFTCOLBLANK);
    SMS_disableLineInterrupt();
    SMS_setBGScrollX(0);
}
