#include "common.h"


extern int D_006A6990[];
INCLUDE_ASM("asm/nonmatchings/ios/message", iosMsgQueueCreate);

INCLUDE_ASM("asm/nonmatchings/ios/message", iosMsgQueueDestroy);

INCLUDE_ASM("asm/nonmatchings/ios/message", send_signal_message);

INCLUDE_ASM("asm/nonmatchings/ios/message", iosMsgSetEvent);

INCLUDE_ASM("asm/nonmatchings/ios/message", func_0013A498);

void iosMsgInit(void)
{
    int *p = D_006A6990;
    int i;
    p += 0xFF;
    for (i = 0xFF; i >= 0; i--) {
        *p = 0;
        p--;
    }
}

INCLUDE_ASM("asm/nonmatchings/ios/message", iosMsgSend);

INCLUDE_ASM("asm/nonmatchings/ios/message", iosMsgRecv);

INCLUDE_ASM("asm/nonmatchings/ios/message", iosMsgQueueDestroyAll);

