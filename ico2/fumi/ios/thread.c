#include "debug.h"
#include "memory.h"
#include "message.h"
#include <eekernel.h>
#include "debug_exception.h"
#include "ios.h"
#include "thread.h"

/* ---------------------------------------------------------------------------
 * EMISSION ORDER / INLINE MODEL of this TU, proven from baserom/pal/SRCFILE.TXT
 * (the retail PAL disc's objdump -dl listing of a January-2002 link; a DIFFERENT
 * link, so no address in it is ever copied here) plus a measurement of the
 * compiler itself.
 *
 * Exactly ONE function of this TU is inlined into another: iosThreadCreate
 * (source lines 111-155).  Its body's lines 119-155 appear inside the listing
 * blocks of iosThreadCreateS (thread.c:171) and iosThreadInit; every other
 * block's line span lies inside its own function.  iosThreadCreate is still a
 * PUBLIC function with 10 external call sites and a real out-of-line copy, so
 * it is a plain `inline`, not `static inline` and not `extern inline`.
 *
 * ee-gcc 2.9 emits a plain-`inline` function's out-of-line copy NOT where it is
 * defined but at the END of the object, and it emits the deferred copies in the
 * order the identifiers were first DECLARED.  Measured on this compiler with a
 * probe TU: prototyped inlines come first, in PROTOTYPE order; the ones with no
 * prototype follow, in definition order.  That is the whole explanation for the
 * ROM object's out-of-source-order tail
 *
 *   ... Resume | iosThreadCreate GetPri GetIOSThreadFromId Wakeup Join
 *       CancelWakeup SemaCreate SemaDelete SemaWait SemaSignal SemaReferStatus
 *       | DestroyMgr AllQuit
 *
 * which is exactly the prototype block below followed by the two functions that
 * have no prototype (DestroyMgr, declared further down for iosThreadInit's use;
 * AllQuit, declared only by its definition, last in the file).  Keep the block's
 * ORDER: it is what places every deferred copy at its ROM address, and the whole
 * object's function offsets are checked against the ROM by nm.
 *
 * This file is now in the dev's SOURCE order, the deferred members interleaved
 * where the listing puts them.  That order is not cosmetic: a string literal is
 * emitted into `.rodata` where the function that first uses it is DEFINED, not
 * where a deferred `inline` copy is finally written out, so the source order is
 * what fixes the order of this TU's seventeen strings.  Measured: with the
 * deferred members parked at the end the run comes out with "th:msg %d\n" ahead
 * of "thr:id out of range\n" and iosThreadDestroyMgr's two strings at the end;
 * in the order below it is byte-identical to the ROM run at 0x551DB0.  The
 * source order the listing gives is:
 *
 *   85 Main | 111 Create | 171 CreateS | 199 Start | 215 Stop | 244 Sleep
 *   | 272 Wakeup | 299 DestroyMgr | 332 Destroy | 397 GetPri | 416 SetPri
 *   | 448 GetIOSThreadFromId | 470 Message | 498 Join | 536 Name | 550 Suspend
 *   | 564 Resume | 580 CancelWakeup | 597 SemaCreate | 619 SemaDelete
 *   | 640 SemaWait | 662 SemaSignal | 683 SemaReferStatus | ~705 Init
 *   | 723 AllQuit
 *
 * (iosThreadInit is NOT at line 111 as an earlier note in this file claimed:
 * 111 is only its first line NOTE, emitted by the inlined callee's parameter
 * copies.  Its own single line is 709, the iosThreadStart tail sibcall, which
 * puts its definition in the 693-722 gap and makes it the last non-deferred
 * function in source order.)
 * ------------------------------------------------------------------------- */

/* .bss, owned by thread.o and reached only from this file (MAIN.MAP names no
   symbol in the run), in the ROM's run order: the IOSThread each thread id
   maps to, the destroy manager's own message queue, the boot thread and its
   8 KB stack. */
static IOSThread *iosThreadTable[256];

static IosMsgQueue iosThreadDestroyQueue;

static IOSThread iosBootThread;

/* a thread stack, 16-byte aligned as the kernel's CreateThread requires; the
   alignment is the ROM's, whose .bss puts 8 B of fill between pad.o's run and
   this object's */
static char iosBootStack[8192] __attribute__((aligned(16)));

void iosThreadMain(void *arg)
{
    int idx = GetThreadId();
    IOSThread *obj = iosThreadTable[idx];
    obj->func(arg);
    if (obj->sleeping == 0) {
        iosThreadSetPri(obj, 33);
    } else {
        iosThreadSetPri(obj, 34);
    }
}

/* 16-byte guard word stamped at both ends of a thread stack */
typedef struct {
    char c[16];
} IosStackMark;

extern int _gp; /* linker-defined global pointer */

static int n_thread = 0; /* derived name: the number of live IOS threads */

inline void iosThreadDestroyMgr(); /* deferred-tail member; see the emission-order note */
/* kept local: agrees with mv_defs.h, which this TU does not include */
extern void __assert(const char *file, int line, const char *expr);

/* thread.c:111 - iosThreadCreate.  It is a PUBLIC function (10 external call
 * sites in the ROM) that gcc 2.9 also inlines into its two in-TU callers,
 * iosThreadCreateS (thread.c:171) and iosThreadInit (thread.c:~705): both of
 * those blocks in baserom/pal/SRCFILE.TXT carry this body's lines 119-155, and
 * its own out-of-line copy sits between iosThreadInit and iosThreadGetPri in
 * BOTH the ROM (0x0013FAE8) and the listing's separate link.  So it is spelled
 * `inline` (not `static inline`, not `extern inline`): gcc 2.9 defers the
 * out-of-line copy of a plain `inline` to the end of the object.  See the
 * emission-order note at the top of this file for why that lands it here. */
inline void iosThreadCreate(IOSThread *th, int no, void (*func)(), int arg, void *stack,
                            long stackSize, int pri)
{
    th->param.entry = iosThreadMain;
    th->func = func;

    th->param.stack = stack;
    *(IosStackMark *)stack = *(const IosStackMark *)"<THREAD_SP>....";
    *(IosStackMark *)((char *)stack + stackSize - 16) = *(const IosStackMark *)"<THREAD_SP_END>";

    th->param.stackSize = stackSize - 16;
    th->param.gpReg = &_gp;
    th->param.initPriority = pri;
    th->param.currentPriority = pri;
    th->id = CreateThread(&th->param);
    th->sleeping = 0;

    th->arg = arg;

    if (th->id >= 0x100) {
        debug_StdPrintfDummy("thr:thread table over flow\n");
        debug_assert(__FILE__, 141);
        __assert(__FILE__, 141, "0");
    } else if (th->id <= 0) {
        debug_StdPrintfDummy("thr:can't create thread\n");
        debug_assert(__FILE__, 145);
        __assert(__FILE__, 145, "0");
    } else {
        iosThreadTable[th->id] = th;
    }

    n_thread++;
    debug_StdPrintfDummy("n_thread %d\n", n_thread);
    th->flags &= ~1;

    th->hasQueue = 0;
}

/* thread.c:171 - iosThreadCreateS: iosThreadCreate over a malloc'd stack.
 * flags bit 0 marks "this stack came from the heap"; iosThreadDestroyMgr
 * reads it back and frees the stack. */
void iosThreadCreateS(IOSThread *th, int no, void (*func)(), int arg, void *heap, long stackSize,
                      int pri)
{
    void *stack;

    stack = iosMallocDebug(heap, stackSize, __FILE__, 173);
    if (stack == 0) {
        debug_StdPrintfDummy("thr:can't create stack\n");
        return;
    }
    iosThreadCreate(th, no, func, arg, stack, stackSize, pri);
    th->flags |= 1;
}

void iosThreadStart(IOSThread *th)
{
    StartThread(th->id, (void *)th->arg);
}

void iosThreadStop(IOSThread *th)
{
    if (th == 0) {
        ExitThread();
    } else {
        TerminateThread(th->id);
    }
}

void iosThreadSleep(void)
{
    SleepThread();
}

inline int iosThreadWakeup(IOSThread *th)
{
    return WakeupThread(th->id);
}

/* thread.c:299 - the destroy-manager thread body.  iosThreadInit creates a
 * thread running this; iosThreadDestroy posts the dying IOSThread to its
 * message queue and this loop does the actual teardown.  Never returns. */
/* .sbss, owned by thread.o and reached only from this file: the manager
   queue's 2-slot message ring. */
static int iosThreadDestroyRing[2];

inline void iosThreadDestroyMgr(void)
{
    IOSThread *th;
    int id;

    debug_StdPrintfDummy("iosThreadDestroyMgr() in\n");

    iosMsgQueueCreate(&iosThreadDestroyQueue, iosThreadDestroyRing, 2);
    while (1) {
        iosMsgRecv(&iosThreadDestroyQueue, (int *)&th, 1);

        id = th->id;
        n_thread--;
        debug_StdPrintfDummy("1:n_thread %d\n", n_thread);
        TerminateThread(id);
        DeleteThread(id);
        if ((th->flags & 1) == (unsigned)1)
            iosFree(iosThreadTable[id]->param.stack);

        if (th->hasQueue) {
            iosMsgQueueDestroy(th->queue);
            iosFree(th->queue);
        }
        iosThreadTable[id] = 0;
    }
}

void iosThreadDestroy(IOSThread *th)
{
    IOSThread *a1 = th;
    if (th == 0) {
        a1 = iosThreadTable[GetThreadId()];
    }
    iosMsgSend(&iosThreadDestroyQueue, (int)a1, 0);
}

inline int iosThreadGetPri(IOSThread *th)
{
    IOSThread **base;
    if (th == 0) {
        int idx;
        base = iosThreadTable;
        idx = GetThreadId();
        th = base[idx];
    }
    return th->param.currentPriority;
}

void iosThreadSetPri(IOSThread *th, int pri)
{
    IOSThread *v;
    v = th;
    if (v == 0) {
        v = iosThreadTable[GetThreadId()];
    } else {
        v = th;
    }
    v->param.currentPriority = pri;
    ChangeThreadPriority(v->id, pri);
}

inline IOSThread *iosGetIOSThreadFromId(unsigned int a0)
{
    IOSThread *ret;
    if (a0 < 0x101)
        goto valid;
    debug_StdPrintfDummy("thr:id out of range\n");
    ret = 0;
    goto out;
valid:
    ret = iosThreadTable[a0];
out:
    return ret;
}

void iosThreadMessage(int a0)
{
    IOSThread *obj = iosThreadTable[GetThreadId()];
    int q;
    if (obj->hasQueue == 0) {
        void *r;
        obj->hasQueue = 1;
        r = iosMallocDebug(ios_partition_root, 0x50, __FILE__, 478);
        obj->queue = r;
        iosMsgQueueCreate(r, (int *)((char *)r + 0x30), 8);
    }
    q = iosMsgSend(obj->queue, a0, 0);
    debug_StdPrintfDummy("th:msg %d\n", q);
}

inline int iosThreadJoin(IOSThread *th)
{
    int buf[4];
    if (th->hasQueue == 0) {
        void *r;
        th->hasQueue = 1;
        r = iosMallocDebug(ios_partition_root, 0x50, __FILE__, 506);
        th->queue = r;
        iosMsgQueueCreate(r, (int *)((char *)r + 0x30), 8);
    }
    iosMsgRecv(th->queue, buf, 1);
    debug_StdPrintfDummy("th:thread joined\n");
    return buf[0];
}

/* kept local: agrees with string.h, which this TU does not include */
extern void strcpy();

void iosThreadName(IOSThread *th)
{
    strcpy(th->name);
}

void iosThreadSuspend(IOSThread *th)
{
    SuspendThread(th->id);
}

void iosThreadResume(IOSThread *th)
{
    ResumeThread(th->id);
}

inline int iosThreadCancelWakeup(IOSThread *th)
{
    int v;
    if (th == 0) {
        v = GetThreadId();
    } else {
        v = th->id;
    }
    return CancelWakeupThread(v);
}

inline int iosSemaCreate(IosSema *self, int initCount, int maxCount, int option)
{
    int rv;
    self->param.initCount = initCount;
    self->param.maxCount = maxCount;
    self->param.option = option;
    rv = CreateSema(&self->param);
    self->id = rv;
    if (rv < 0) {
        debug_StdPrintfDummy("sem: can't create %d\n", rv);
        debug_assert(__FILE__, 604);
        __assert(__FILE__, 604, "0");
        return self->id;
    }
    return 0;
}

inline int iosSemaDelete(IosSema *self)
{
    int rv = DeleteSema(self->id);
    if (rv < 0) {
        debug_StdPrintfDummy("sem: can't delete %d\n", self->id);
        debug_assert(__FILE__, 624);
        __assert(__FILE__, 624, "0");
        return rv;
    }
    return 0;
}

inline int iosSemaWait(IosSema *self)
{
    int rv = ReferSemaStatus(self->id, &self->param);
    if (rv < 0) {
        debug_StdPrintfDummy("sem: wait error? %d\n", self->id);
        return rv;
    }
    WaitSema(self->id);
    return 0;
}

inline int iosSemaSignal(IosSema *self)
{
    int v;
    int rv;
    v = SignalSema(self->id);
    rv = 0;
    if (v < 0) {
        debug_StdPrintfDummy("sem: signal error? %d\n", self->id);
        rv = v;
    }
    return rv;
}

inline int iosSemaReferStatus(IosSema *self)
{
    int rv = ReferSemaStatus(self->id, &self->status);
    if (rv < 0) {
        debug_StdPrintfDummy("sem: refer error? %d\n", self->id);
        debug_assert(__FILE__, 688);
        __assert(__FILE__, 688, "0");
        return rv;
    }
    return 0;
}

void iosThreadInit(void)
{
    iosThreadCreate(&iosBootThread, 0, iosThreadDestroyMgr, 0, iosBootStack, 8192, 13);
    iosThreadStart(&iosBootThread);
}

/* thread.c:723, the last function of the TU.  Never called anywhere in the
 * retail ELF; the PAL listing puts it last in the object's deferred-`inline`
 * tail, and a plain definition in this file position emits the same bytes. */
inline void iosThreadAllQuit(int self)
{
    int i;

    for (i = 0; i < 256; i++) {
        if (iosThreadTable[i] != 0 && i != self) {
            iosThreadDestroy(iosThreadTable[i]);
        }
    }
}
