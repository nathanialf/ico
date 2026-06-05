#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/message", deq_mes_th);

extern void func_00100540(int a0);

void iosMsgQueueCreate(int *a0) {
    int *node = (int *)a0[4];
    if (node) {
        int next = node[0x11];
        int arg = a0[0xB];
        a0[4] = next;
        node[0x11] = 0;
        func_00100540(arg);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/message", iosMsgQueueDestroy);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/message", send_signal_message);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/message", iosMsgSetEvent);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/message", func_00139F80);

extern int D_006A0510[];

void iosMsgInit(void) {
    int i;
    for (i = 0xFF; i >= 0; i--) {
        D_006A0510[i] = 0;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/message", iosMsgSend);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/message", iosMsgRecv);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/message", iosMsgQueueDestroyAll);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_006A0510;  /* stride 0x4 */

/* end struct shapes */
