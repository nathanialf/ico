#include "common.h"

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

extern void SignalSema(int sema);

void deq_mes_th(IosMsgQueue *self)
{
    IosMsg *msg = self->head;

    if (msg != 0) {
        self->head = msg->next;
        msg->next = 0;
        SignalSema(self->sema);
    }
}
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
extern char D_00551A80[];
extern char D_00551A60[];
extern char D_0063A510[];
int iosMsgRecv(char *q, int *out, int mode) {
    int st[8];
    if (q == 0) {
        debug_StdPrintfDummy(D_00551A80);
        func_001B6250(D_00551A60, 0x149);
        __assert(D_00551A60, 0x149, D_0063A510);
    }
    ReferSemaStatus(*(int *)(q + 0x2C), st);
    if (*(int *)(q + 8) == 0) {
        if (mode != 1) return -1;
        WaitSema(*(int *)(q + 0x2C));
    }
    *out = (*(int **)q)[*(int *)(q + 4)];
    *(int *)(q + 4) = (*(int *)(q + 4) + 1) % st[1];
    *(int *)(q + 8) -= 1;
    if (*(int *)(q + 8) == st[1]) {
        if (st[3] > 0) {
            SignalSema(*(int *)(q + 0x2C));
        }
    }
    return 0;
}
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
extern int odd_even;
extern int *D_0063A530;
extern void iWakeupThread(int);

int signal_handler(int a0) {
    if (a0 == 2) {
        volatile unsigned long long *reg = (volatile unsigned long long *)0x12001000;
        odd_even = (int)(((*reg >> 13) & 1) ^ 1);
        iWakeupThread(D_0063A530[12]);
    }
    return 0;
}
