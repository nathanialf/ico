#include "common.h"

INCLUDE_ASM("asm/nonmatchings/ios/message", deq_mes_th);
INCLUDE_ASM("asm/nonmatchings/ios/message", iosMsgQueueCreate);
INCLUDE_ASM("asm/nonmatchings/ios/message", iosMsgQueueDestroy);
INCLUDE_ASM("asm/nonmatchings/ios/message", func_0013C608);
INCLUDE_ASM("asm/nonmatchings/ios/message", func_0013C720);
extern int D_006BC938[];

void iosMsgInit(void)
{
    int *p = D_006BC938;
    int i;
    p += 0xFF;
    for (i = 0xFF; i >= 0; i--) {
        *p = 0;
        p--;
    }
}
INCLUDE_ASM("asm/nonmatchings/ios/message", iosMsgSend);
INCLUDE_ASM("asm/nonmatchings/ios/message", iosMsgRecv);
extern int iosMsgQueueDestroy(int a0);

void iosMsgQueueDestroyAll(void) {
    int *p;
    int i;
    int **q = (int **)D_006BC938;
    i = 0xFF;
    do {
        p = *q++;
        if (p != 0) {
            iosMsgQueueDestroy(p);
        }
        i--;
    } while (i >= 0);
}
extern int D_00639CD0;
extern int *D_0063A530;
extern void iWakeupThread(int);

int signal_handler(int a0) {
    if (a0 == 2) {
        volatile unsigned long long *reg = (volatile unsigned long long *)0x12001000;
        D_00639CD0 = (int)(((*reg >> 13) & 1) ^ 1);
        iWakeupThread(D_0063A530[12]);
    }
    return 0;
}
