#include "debug.h"
#include "memory.h"
#include <eekernel.h>
#include <eeregs.h>
#include "ios.h"
#include "thread.h"
#include "debug_exception.h"
#include "main.h"
#include "message.h"

typedef struct IosMsg {
    char pad0[68];
    struct IosMsg *next; /* 0x44 */
} IosMsg;

/* the event thread iosMsgSetEvent spawns, one 0x40C0-byte block: the
   IOSThread, its 16 KB stack and three trailing words of its own
   bookkeeping. */
typedef struct MsgEventThread { /* field names derived */
    IOSThread th;               /* 0x0000 */
    char stack[16384];          /* 0x0070, the thread's stack */
    char pad4070[32];
    IosMsgQueue *queue; /* 0x4090 */
    int val;            /* 0x4094 */
    int intc;           /* 0x4098 */
} MsgEventThread;

/* kept local: agrees with mv_defs.h, which this TU does not include */
extern void __assert(const char *file, int line, const char *expr);

/* kept local with message.h's declaration (this TU does not include it): the
   signal thread's record, defined after the functions whose strings precede it */

/* .bss, owned by message.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the queue registered against each semaphore id. */
static int msgQueueTable[256];

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

    q->sem.initCount = 0;
    q->sem.maxCount = size;
    q->sem.attr = 1;
    q->sema = CreateSema(&q->sem);
    if (q->sema < 0) {
        debug_assert("ios/message.c", 120);
        __assert("ios/message.c", 120, "0");
    }
    ((IosMsgQueue **)msgQueueTable)[q->sema] = q;
    debug_StdPrintfDummy("sema[%d] = %p\n", q->sema, q);
}

void iosMsgQueueDestroy(IosMsgQueue *q)
{
    debug_StdPrintfDummy("%p\n", q);
    if (q->sema < 0) {
        debug_assert("ios/message.c", 136);
        __assert("ios/message.c", 136, "0");
    }
    ((IosMsgQueue **)msgQueueTable)[q->sema] = 0;
    DeleteSema(q->sema);
}

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * iosMsgSend into send_signal_message, so it is a public `inline` whose
 * out-of-line copy is emitted at its own ROM slot; the caller here inlines this
 * static stand-in, which collapses at layout. */
static inline int msgSend(IosMsgQueue *q, int val, int mode)
{
    struct SemaParam st;

    if (q == 0) {
        debug_StdPrintfDummy("msg:null message queue\n");
        debug_assert("ios/message.c", 293);
        __assert("ios/message.c", 293, "0");
    }
    ReferSemaStatus(q->sema, &st);
    if (q->num == st.maxCount) {
        if (mode != 1) {
            debug_StdPrintfDummy("MSG NO SEND\n");
            return -1;
        }
        WaitSema(q->sema);
    }
    q->buf[(q->rd + q->num) % st.maxCount] = val;
    q->num += 1;
    if (st.numWaitThreads > 0) {
        SignalSema(q->sema);
    }
    return 0;
}

void send_signal_message(void)
{
    MsgEventThread *self = (MsgEventThread *)iosGetIOSThreadFromId(GetThreadId());
    MsgEventThread *th = (MsgEventThread *)self->th.arg;

    th_sig = (int *)self;
    debug_StdPrintfDummy("%d %d\n", self->th.id, th->val);

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
        debug_StdPrintfDummy("evt:null message queue\n");
    }
    th = iosMallocDebug(ios_partition_event, 0x40C0, "ios/message.c", 453);
    iosThreadCreate(&th->th, 4, send_signal_message, (int)th, th->stack, 0x4000, 0xB);
    th->queue = q;
    th->val = val;
    th->intc = intc;
    iosThreadStart(&th->th);
    debug_StdPrintfDummy("where is here\n");
    AddIntcHandler(intc, signal_handler, -1);
    ret = EnableIntc(intc);
    debug_StdPrintfDummy("evt:%d\n", ret);
    debug_StdPrintfDummy("evt:signal added\n");
}

/* .sdata, after the short strings above: the signal thread's record
   (MAIN.MAP global), which iosMsgInit's handler wakes. */
int *th_sig = 0;

void iosMsgInit(void)
{
    int *p = msgQueueTable;
    int i;
    p += 0xFF;
    for (i = 0xFF; i >= 0; i--) {
        *p = 0;
        p--;
    }
}

int iosMsgSend(IosMsgQueue *q, int val, int mode)
{
    struct SemaParam st;
    if (q == 0) {
        debug_StdPrintfDummy("msg:null message queue\n");
        debug_assert("ios/message.c", 293);
        __assert("ios/message.c", 293, "0");
    }
    ReferSemaStatus(q->sema, &st);
    if (q->num == st.maxCount) {
        if (mode != 1) {
            debug_StdPrintfDummy("MSG NO SEND\n");
            return -1;
        }
        WaitSema(q->sema);
    }
    q->buf[(q->rd + q->num) % st.maxCount] = val;
    q->num += 1;
    if (st.numWaitThreads > 0) {
        SignalSema(q->sema);
    }
    return 0;
}

int iosMsgRecv(IosMsgQueue *q, int *out, int mode)
{
    struct SemaParam st;
    if (q == 0) {
        debug_StdPrintfDummy("msg:null message queue\n");
        debug_assert("ios/message.c", 329);
        __assert("ios/message.c", 329, "0");
    }
    ReferSemaStatus(q->sema, &st);
    if (q->num == 0) {
        if (mode != 1)
            return -1;
        WaitSema(q->sema);
    }
    *out = q->buf[q->rd];
    q->rd = (q->rd + 1) % st.maxCount;
    q->num -= 1;
    if (q->num == st.maxCount) {
        if (st.numWaitThreads > 0) {
            SignalSema(q->sema);
        }
    }
    return 0;
}

void iosMsgQueueDestroyAll(void)
{
    int *p;
    int i;
    int **q = (int **)msgQueueTable;
    i = 0xFF;
    do {
        p = *q++;
        if (p != 0) {
            iosMsgQueueDestroy((IosMsgQueue *)p);
        }
        i--;
    } while (i >= 0);
}

int signal_handler(int a0)
{
    if (a0 == 2) {
        volatile unsigned long long *reg = (volatile unsigned long long *)GS_CSR;
        odd_even = (int)(((*reg >> 13) & 1) ^ 1);
        iWakeupThread(th_sig[12]);
    }
    return 0;
}
