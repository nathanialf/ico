#include "common.h"

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
 * The dev's file was in SOURCE order; this one is in EMISSION order, so the 13
 * deferred members sit after iosThreadInit instead of interleaved.  The source
 * order the listing gives, for reference, is:
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

/* --- ios thread object (SCE ee_thread_t at offset 0 + ICO bookkeeping) --- */
typedef struct IOSThread {
    int status;          /* 0x00 ee_thread_t.status              */
    void (*entry)();     /* 0x04 ee_thread_t.func  == iosThreadMain */
    void *stack;         /* 0x08 ee_thread_t.stack               */
    int stackSize;       /* 0x0C ee_thread_t.stack_size          */
    void *gpReg;         /* 0x10 ee_thread_t.gp_reg              */
    int initPriority;    /* 0x14 ee_thread_t.initial_priority    */
    int currentPriority; /* 0x18 ee_thread_t.current_priority    */
    int attr;            /* 0x1C */
    int option;          /* 0x20 */
    int reserved[3];     /* 0x24 */
    int id;              /* 0x30 kernel thread id                */
    int arg;             /* 0x34 argument handed to func         */
    void (*func)();      /* 0x38 body run by iosThreadMain       */
    int flags;           /* 0x3C */
    int sleeping;        /* 0x40 read by iosThreadMain           */
    int pad44;           /* 0x44 */
    int hasQueue;        /* 0x48 */
    void *queue;         /* 0x4C */
    char name[16];       /* 0x50 */
} IOSThread;

extern void iosThreadCreate(IOSThread *th, int no, void (*func)(), int arg, void *stack,
                            long stackSize, int pri);
extern int iosThreadGetPri(int *a0);
extern int iosGetIOSThreadFromId(unsigned int a0);
extern int iosThreadWakeup(int *self);
extern int iosThreadJoin(void *a0);
extern int iosThreadCancelWakeup(int *self);
extern int iosSemaCreate(int *self, int a1, int a2, int a3);
extern int iosSemaDelete(int *self);
extern int iosSemaWait(int *self);
extern int iosSemaSignal(int *self);
extern int iosSemaReferStatus(int *self);
extern void debug_StdPrintfDummy();
extern int D_006BCEE0[];
extern int GetThreadId();
extern void iosThreadSetPri(int *a0, int a1);

void iosThreadMain(int a0)
{
    int idx = GetThreadId();
    int *obj = (int *)D_006BCEE0[idx];
    (*(void (**)(int))((char *)obj + 0x38))(a0);
    if (*(int *)((char *)obj + 0x40) == 0) {
        iosThreadSetPri((int *)obj, 0x21);
    } else {
        iosThreadSetPri((int *)obj, 0x22);
    }
}

/* 16-byte guard word stamped at both ends of a thread stack */
typedef struct {
    char c[16];
} IosStackMark;

extern IOSThread D_006BD310;      /* the main (boot) IOS thread */
extern char D_006BD380[];         /* its 8 KB stack */
extern int _gp;                   /* linker-defined global pointer */
extern int D_0063A5F0;            /* number of live IOS threads */
extern const char D_00551DB0[16]; /* "<THREAD_SP>...."  */
extern const char D_00551DC0[16]; /* "<THREAD_SP_END>"  */
extern char D_00551DD0[];
extern char D_00551E00[];
extern char D_00551E20[];
inline void iosThreadDestroyMgr(); /* deferred-tail member; see the emission-order note */
extern int CreateThread(IOSThread *param);
extern const char D_00551DF0[];
extern char D_0063A5F8[];
extern void debug_assert(const char *file, int line);
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
    th->entry = iosThreadMain;
    th->func = func;

    th->stack = stack;
    *(IosStackMark *)stack = *(const IosStackMark *)D_00551DB0;
    *(IosStackMark *)((char *)stack + stackSize - 16) = *(const IosStackMark *)D_00551DC0;

    th->stackSize = stackSize - 16;
    th->gpReg = &_gp;
    th->initPriority = pri;
    th->currentPriority = pri;
    th->id = CreateThread(th);
    th->sleeping = 0;

    th->arg = arg;

    if (th->id >= 0x100) {
        debug_StdPrintfDummy(D_00551DD0);
        debug_assert(D_00551DF0, 0x8D);
        __assert(D_00551DF0, 0x8D, D_0063A5F8);
    } else if (th->id <= 0) {
        debug_StdPrintfDummy(D_00551E00);
        debug_assert(D_00551DF0, 0x91);
        __assert(D_00551DF0, 0x91, D_0063A5F8);
    } else {
        D_006BCEE0[th->id] = (int)th;
    }

    D_0063A5F0++;
    debug_StdPrintfDummy(D_00551E20, D_0063A5F0);
    th->flags &= ~1;

    th->hasQueue = 0;
}

extern char D_00551E30[];
extern void *iosMallocDebug(void *a, int n, void *c, int d);

/* thread.c:171 - iosThreadCreateS: iosThreadCreate over a malloc'd stack.
 * flags bit 0 marks "this stack came from the heap"; iosThreadDestroyMgr
 * reads it back and frees the stack. */
void iosThreadCreateS(IOSThread *th, int no, void (*func)(), int arg, void *heap, long stackSize,
                      int pri)
{
    void *stack;

    stack = iosMallocDebug(heap, stackSize, (void *)D_00551DF0, 0xAD);
    if (stack == 0) {
        debug_StdPrintfDummy(D_00551E30);
        return;
    }
    iosThreadCreate(th, no, func, arg, stack, stackSize, pri);
    th->flags |= 1;
}

extern void StartThread();

void iosThreadStart(int a0)
{
    StartThread(*(int *)(a0 + 0x30), *(int *)(a0 + 0x34));
}

extern void ExitThread();
extern void TerminateThread();

void iosThreadStop(int a0)
{
    if (a0 == 0) {
        ExitThread();
    } else {
        TerminateThread(*(int *)(a0 + 0x30));
    }
}

extern void SleepThread();

void iosThreadSleep(int a0, int a1, int a2, int a3)
{
    SleepThread(a0, a1, a2, a3);
}

extern int D_006BCEE0[];
extern char D_006BD2E0[];
extern int GetThreadId();
extern int iosMsgSend(int *self, int a1, int a2);

void iosThreadDestroy(int a0)
{
    int a1 = a0;
    if (a0 == 0) {
        a1 = D_006BCEE0[GetThreadId()];
    }
    iosMsgSend(D_006BD2E0, a1, 0);
}

extern void ChangeThreadPriority();

void iosThreadSetPri(int *a0, int a1)
{
    int *v;
    v = a0;
    if (v == 0) {
        v = (int *)D_006BCEE0[GetThreadId()];
    } else {
        v = a0;
    }
    v[0x18 / 4] = a1;
    ChangeThreadPriority(v[0x30 / 4], a1);
}

extern const char D_00551DF0[];
extern char D_00551E90[];
extern void *D_0063A428;
extern void *iosMallocDebug(void *a, int n, void *c, int d);
extern void iosMsgQueueCreate(void *a, void *b, int c);

void iosThreadMessage(int a0)
{
    void *obj = (void *)D_006BCEE0[GetThreadId()];
    int q;
    if (*(int *)((char *)obj + 0x48) == 0) {
        void *r;
        *(int *)((char *)obj + 0x48) = 1;
        r = iosMallocDebug(D_0063A428, 0x50, (void *)D_00551DF0, 0x1DE);
        *(void **)((char *)obj + 0x4C) = r;
        iosMsgQueueCreate(r, (char *)r + 0x30, 8);
    }
    q = iosMsgSend((char *)*(void **)((char *)obj + 0x4C), a0, 0);
    debug_StdPrintfDummy(D_00551E90, q);
}

extern void strcpy();

void iosThreadName(int a0)
{
    strcpy(a0 + 0x50);
}

extern void SuspendThread();

void iosThreadSuspend(int a0)
{
    SuspendThread(*(int *)(a0 + 0x30));
}

extern void ResumeThread();

void iosThreadResume(int a0)
{
    ResumeThread(*(int *)(a0 + 0x30));
}

void iosThreadInit(void)
{
    iosThreadCreate(&D_006BD310, 0, iosThreadDestroyMgr, 0, D_006BD380, 0x2000, 13);
    iosThreadStart((int)&D_006BD310);
}

inline int iosThreadGetPri(int *a0)
{
    int **base;
    if (a0 == 0) {
        int idx;
        base = D_006BCEE0;
        idx = GetThreadId();
        a0 = base[idx];
    }
    return a0[0x18 / 4];
}

extern char D_00551E78[];

inline int iosGetIOSThreadFromId(unsigned int a0)
{
    int ret;
    if (a0 < 0x101)
        goto valid;
    debug_StdPrintfDummy(D_00551E78);
    ret = 0;
    goto out;
valid:
    ret = D_006BCEE0[a0];
out:
    return ret;
}

extern int WakeupThread();

inline int iosThreadWakeup(int *self)
{
    return WakeupThread(self[0x30 / 4]);
}

extern char D_00551EA0[];
extern int iosMsgRecv(void *a, void *b, int c);

inline int iosThreadJoin(void *a0)
{
    int buf[4];
    if (*(int *)((char *)a0 + 0x48) == 0) {
        void *r;
        *(int *)((char *)a0 + 0x48) = 1;
        r = iosMallocDebug(D_0063A428, 0x50, (void *)D_00551DF0, 0x1FA);
        *(void **)((char *)a0 + 0x4C) = r;
        iosMsgQueueCreate(r, (char *)r + 0x30, 8);
    }
    iosMsgRecv(*(void **)((char *)a0 + 0x4C), buf, 1);
    debug_StdPrintfDummy(D_00551EA0);
    return buf[0];
}

extern int CancelWakeupThread();

inline int iosThreadCancelWakeup(int *self)
{
    int v;
    if (self == 0) {
        v = GetThreadId();
    } else {
        v = self[0x30 / 4];
    }
    return CancelWakeupThread(v);
}

extern int CreateSema(int *self);
extern char D_00551EB8[];
extern char D_0063A5F8[];
extern void __assert(const char *file, int line, const char *expr);
extern void debug_assert(const char *file, int line);

inline int iosSemaCreate(int *self, int a1, int a2, int a3)
{
    int rv;
    self[0x8 / 4] = a1;
    self[0x4 / 4] = a2;
    self[0x14 / 4] = a3;
    rv = CreateSema(self);
    self[0x30 / 4] = rv;
    if (rv < 0) {
        debug_StdPrintfDummy(D_00551EB8, rv);
        debug_assert(D_00551DF0, 0x25C);
        __assert(D_00551DF0, 0x25C, D_0063A5F8);
        return self[0x30 / 4];
    }
    return 0;
}

extern char D_00551ED0[];
extern int DeleteSema(int sem);

inline int iosSemaDelete(int *self)
{
    int rv = DeleteSema(self[0x30 / 4]);
    if (rv < 0) {
        debug_StdPrintfDummy(D_00551ED0, self[0x30 / 4]);
        debug_assert(D_00551DF0, 0x270);
        __assert(D_00551DF0, 0x270, D_0063A5F8);
        return rv;
    }
    return 0;
}

extern char D_00551EE8[];
extern int ReferSemaStatus(int sem, int *self);
extern int WaitSema(int sem);

inline int iosSemaWait(int *self)
{
    int rv = ReferSemaStatus(self[0x30 / 4], self);
    if (rv < 0) {
        debug_StdPrintfDummy(D_00551EE8, self[0x30 / 4]);
        return rv;
    }
    WaitSema(self[0x30 / 4]);
    return 0;
}

extern char D_00551F00[];
extern int SignalSema(int x);

inline int iosSemaSignal(int *self)
{
    int v;
    int rv;
    v = SignalSema(self[0x30 / 4]);
    rv = 0;
    if (v < 0) {
        debug_StdPrintfDummy(D_00551F00, self[0x30 / 4]);
        rv = v;
    }
    return rv;
}

extern char D_00551F18[];

inline int iosSemaReferStatus(int *self)
{
    int rv = ReferSemaStatus(self[0x30 / 4], self + 0x18 / 4);
    if (rv < 0) {
        debug_StdPrintfDummy(D_00551F18, self[0x30 / 4]);
        debug_assert(D_00551DF0, 0x2B0);
        __assert(D_00551DF0, 0x2B0, D_0063A5F8);
        return rv;
    }
    return 0;
}

/* thread.c:299 - the destroy-manager thread body.  iosThreadInit creates a
 * thread running this; iosThreadDestroy posts the dying IOSThread to its
 * message queue and this loop does the actual teardown.  Never returns. */
extern char D_00551E48[]; /* "iosThreadDestroyMgr() in\n" */
extern char D_00551E68[]; /* "1:n_thread %d\n"           */
extern int D_0063C1A0[2]; /* the manager queue's 2-slot message ring */
extern void iosFree(void *p);
extern void iosMsgQueueDestroy(void *q);
extern void DeleteThread(int id);

inline void iosThreadDestroyMgr(void)
{
    IOSThread *th;
    int id;

    debug_StdPrintfDummy(D_00551E48);

    iosMsgQueueCreate(D_006BD2E0, D_0063C1A0, 2);
    while (1) {
        iosMsgRecv(D_006BD2E0, &th, 1);

        id = th->id;
        D_0063A5F0--;
        debug_StdPrintfDummy(D_00551E68, D_0063A5F0);
        TerminateThread(id);
        DeleteThread(id);
        if ((th->flags & 1) == (unsigned)1)
            iosFree(((IOSThread *)D_006BCEE0[id])->stack);

        if (th->hasQueue) {
            iosMsgQueueDestroy(th->queue);
            iosFree(th->queue);
        }
        D_006BCEE0[id] = 0;
    }
}

/* thread.c:723 — the last function of the TU.  Never called anywhere in the
 * retail ELF; the PAL listing puts it last in the object's deferred-`inline`
 * tail, and a plain definition in this file position emits the same bytes. */
inline void iosThreadAllQuit(int self)
{
    int i;

    for (i = 0; i < 0x100; i++) {
        if (D_006BCEE0[i] != 0 && i != self) {
            iosThreadDestroy(D_006BCEE0[i]);
        }
    }
}
