#include "common.h"


extern int D_006A6990[];

extern void func_00100540(int sema);

typedef struct IosMsg {
    char pad0[0x44];
    struct IosMsg *next;        /* 0x44 */
} IosMsg;

typedef struct IosMsgQueue {
    char pad0[0x10];
    IosMsg *head;               /* 0x10 */
    char pad14[0x18];
    int sema;                   /* 0x2C */
} IosMsgQueue;

void iosMsgQueueCreate(IosMsgQueue *self)
{
    IosMsg *msg = self->head;

    if (msg != 0) {
        self->head = msg->next;
        msg->next = 0;
        func_00100540(self->sema);
    }
}

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

extern int send_signal_message(int a0);

void iosMsgQueueDestroyAll(void) {
    int *p;
    int i;
    int **q = (int **)D_006A6990;
    i = 0xFF;
    do {
        p = *q++;
        if (p != 0) {
            send_signal_message(p);
        }
        i--;
    } while (i >= 0);
}

