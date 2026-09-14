#include "common.h"

typedef struct IosMsg {
    char pad0[0x44];
    struct IosMsg *next; /* 0x44 */
} IosMsg;

/* SCE ee_sema_t, the parameter block CreateSema is handed. */
typedef struct EeSema {
    int count;        /* 0x00 */
    int max_count;    /* 0x04 */
    int init_count;   /* 0x08 */
    int wait_threads; /* 0x0C */
    int attr;         /* 0x10 */
    int option;       /* 0x14 */
} EeSema;

typedef struct IosMsgQueue {
    int *buf;     /* 0x00 */
    int rd;       /* 0x04 */
    int num;      /* 0x08 */
    int size;     /* 0x0C */
    IosMsg *head; /* 0x10 */
    EeSema sem;   /* 0x14 */
    int sema;     /* 0x2C */
} IosMsgQueue;

/* the event thread iosMsgSetEvent spawns: an IOSThread with three trailing
   words of its own bookkeeping. */
typedef struct MsgEventThread {
    char pad0[0x30];
    int id;  /* 0x0030 IOSThread.id  */
    int arg; /* 0x0034 IOSThread.arg */
    char pad38[0x4058];
    IosMsgQueue *queue; /* 0x4090 */
    int val;            /* 0x4094 */
    int intc;           /* 0x4098 */
} MsgEventThread;

extern void SignalSema(int sema);
extern int CreateSema(EeSema *p);
extern int DeleteSema(int sema);
extern int ReferSemaStatus(int sema, int *st);
extern int WaitSema(int sema);
extern void debug_StdPrintfDummy();
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern int GetThreadId();
extern int iosGetIOSThreadFromId(unsigned int a0);
extern void iosThreadSleep(void);
extern void iosThreadCreate(void *th, int no, void (*func)(), int arg, void *stack, long stackSize,
                            int pri);
extern void iosThreadStart(int a0);
extern int AddIntcHandler(int ch, void *fn, int a2);
extern int EnableIntc(int ch);
extern void *iosMallocDebug(int handle, int size, char *file, int line);
extern int signal_handler(int a0);
extern int D_0063A42C;
extern int *D_0063A530;
extern int D_006BC938[];
extern char D_00551A60[];
extern char D_00551A70[];
extern char D_00551A80[];
extern char D_00551A98[];
extern char D_00551AA8[];
extern char D_00551AC0[];
extern char D_00551AD0[];
extern char D_0063A510[];
extern char D_0063A518[];
extern char D_0063A520[];
extern char D_0063A528[];

void deq_mes_th(IosMsgQueue *self)
{
    IosMsg *msg = self->head;

    if (msg != 0) {
        self->head = msg->next;
        msg->next = 0;
        SignalSema(self->sema);
    }
}

void iosMsgQueueCreate(IosMsgQueue *q, int *buf, int size)
{
    q->buf = buf;
    q->rd = 0;
    q->num = 0;

    q->head = 0;
    q->size = size;

    q->sem.init_count = 0;
    q->sem.max_count = size;
    q->sem.attr = 1;
    q->sema = CreateSema(&q->sem);
    if (q->sema < 0) {
        debug_assert(D_00551A60, 0x78);
        __assert(D_00551A60, 0x78, D_0063A510);
    }
    ((IosMsgQueue **)D_006BC938)[q->sema] = q;
    debug_StdPrintfDummy(D_00551A70, q->sema, q);
}

void iosMsgQueueDestroy(IosMsgQueue *q)
{
    debug_StdPrintfDummy(D_0063A518, q);
    if (q->sema < 0) {
        debug_assert(D_00551A60, 0x88);
        __assert(D_00551A60, 0x88, D_0063A510);
    }
    ((IosMsgQueue **)D_006BC938)[q->sema] = 0;
    DeleteSema(q->sema);
}

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * iosMsgSend into send_signal_message, so it is a public `inline` whose
 * out-of-line copy is emitted at its own ROM slot; the caller here inlines this
 * static stand-in, which collapses at layout. */
static inline int msgSend(IosMsgQueue *q, int val, int mode)
{
    int st[8];

    if (q == 0) {
        debug_StdPrintfDummy(D_00551A80);
        debug_assert(D_00551A60, 0x125);
        __assert(D_00551A60, 0x125, D_0063A510);
    }
    ReferSemaStatus(q->sema, st);
    if (q->num == st[1]) {
        if (mode != 1) {
            debug_StdPrintfDummy(D_00551A98);
            return -1;
        }
        WaitSema(q->sema);
    }
    q->buf[(q->rd + q->num) % st[1]] = val;
    q->num += 1;
    if (st[3] > 0) {
        SignalSema(q->sema);
    }
    return 0;
}

void send_signal_message(void)
{
    MsgEventThread *self = (MsgEventThread *)iosGetIOSThreadFromId(GetThreadId());
    MsgEventThread *th = (MsgEventThread *)self->arg;

    D_0063A530 = (int *)self;
    debug_StdPrintfDummy(D_0063A520, self->id, th->val);

    for (;;) {
        iosThreadSleep();
        msgSend(th->queue, th->val, 0);
    }
}

void iosMsgSetEvent(int intc, IosMsgQueue *q, int val)
{
    MsgEventThread *th;
    int ret;

    if (q == 0) {
        debug_StdPrintfDummy(D_00551AA8);
    }
    th = iosMallocDebug(D_0063A42C, 0x40C0, D_00551A60, 0x1C5);
    iosThreadCreate(th, 4, send_signal_message, (int)th, (char *)th + 0x70, 0x4000, 0xB);
    th->queue = q;
    th->val = val;
    th->intc = intc;
    iosThreadStart((int)th);
    debug_StdPrintfDummy(D_00551AC0);
    AddIntcHandler(intc, signal_handler, -1);
    ret = EnableIntc(intc);
    debug_StdPrintfDummy(D_0063A528, ret);
    debug_StdPrintfDummy(D_00551AD0);
}

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

extern char D_00551A80[];
extern char D_00551A60[];
extern char D_0063A510[];
extern char D_00551A98[];

int iosMsgSend(char *q, int val, int mode)
{
    int st[8];
    if (q == 0) {
        debug_StdPrintfDummy(D_00551A80);
        debug_assert(D_00551A60, 0x125);
        __assert(D_00551A60, 0x125, D_0063A510);
    }
    ReferSemaStatus(*(int *)(q + 0x2C), st);
    if (*(int *)(q + 8) == st[1]) {
        if (mode != 1) {
            debug_StdPrintfDummy(D_00551A98);
            return -1;
        }
        WaitSema(*(int *)(q + 0x2C));
    }
    (*(int **)q)[(*(int *)(q + 4) + *(int *)(q + 8)) % st[1]] = val;
    *(int *)(q + 8) += 1;
    if (st[3] > 0) {
        SignalSema(*(int *)(q + 0x2C));
    }
    return 0;
}

extern char D_00551A80[];
extern char D_00551A60[];
extern char D_0063A510[];

int iosMsgRecv(char *q, int *out, int mode)
{
    int st[8];
    if (q == 0) {
        debug_StdPrintfDummy(D_00551A80);
        debug_assert(D_00551A60, 0x149);
        __assert(D_00551A60, 0x149, D_0063A510);
    }
    ReferSemaStatus(*(int *)(q + 0x2C), st);
    if (*(int *)(q + 8) == 0) {
        if (mode != 1)
            return -1;
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

void iosMsgQueueDestroyAll(void)
{
    int *p;
    int i;
    int **q = (int **)D_006BC938;
    i = 0xFF;
    do {
        p = *q++;
        if (p != 0) {
            iosMsgQueueDestroy((IosMsgQueue *)p);
        }
        i--;
    } while (i >= 0);
}

extern int odd_even;
extern int *D_0063A530;
extern void iWakeupThread(int);

int signal_handler(int a0)
{
    if (a0 == 2) {
        volatile unsigned long long *reg = (volatile unsigned long long *)0x12001000;
        odd_even = (int)(((*reg >> 13) & 1) ^ 1);
        iWakeupThread(D_0063A530[12]);
    }
    return 0;
}
