#include "common.h"

extern int D_006BCEE0[];
extern int GetThreadId();
extern void iosThreadSetPri(int *a0, int a1);

void iosThreadMain(int a0)
{
    int idx = GetThreadId();
    int *obj = (int *) D_006BCEE0[idx];
    (*(void (**)(int))((char *) obj + 0x38))(a0);
    if (*(int *)((char *) obj + 0x40) == 0)
    {
        iosThreadSetPri((int *)obj, 0x21);
    }
    else
    {
        iosThreadSetPri((int *)obj, 0x22);
    }
}
INCLUDE_ASM("asm/nonmatchings/ios/thread", iosThreadCreateS);
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
  if (v == 0)
  {
    v = (int *) D_006BCEE0[GetThreadId()];
  }
  else
  {
    v = a0;
  }
  v[0x18 / 4] = a1;
  ChangeThreadPriority(v[0x30 / 4], a1);
}
extern const char D_00551DF0[];
extern char D_00551E90[];
extern void *D_0063A428;
extern extern void debug_StdPrintfDummy();
extern void *iosMallocDebug(void *a, int n, void *c, int d);
extern void iosMsgQueueCreate(void *a, void *b, int c);

void iosThreadMessage(int a0) {
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
/* --- ios thread object (SCE ee_thread_t at offset 0 + ICO bookkeeping) --- */
typedef struct IOSThread {
    int status;                 /* 0x00 ee_thread_t.status              */
    void (*entry)();            /* 0x04 ee_thread_t.func  == iosThreadMain */
    void *stack;                /* 0x08 ee_thread_t.stack               */
    int stackSize;              /* 0x0C ee_thread_t.stack_size          */
    void *gpReg;                /* 0x10 ee_thread_t.gp_reg              */
    int initPriority;           /* 0x14 ee_thread_t.initial_priority    */
    int currentPriority;        /* 0x18 ee_thread_t.current_priority    */
    int attr;                   /* 0x1C */
    int option;                 /* 0x20 */
    int reserved[3];            /* 0x24 */
    int id;                     /* 0x30 kernel thread id                */
    int arg;                    /* 0x34 argument handed to func         */
    void (*func)();             /* 0x38 body run by iosThreadMain       */
    int flags;                  /* 0x3C */
    int sleeping;               /* 0x40 read by iosThreadMain           */
    int pad44;                  /* 0x44 */
    int hasQueue;               /* 0x48 */
    void *queue;                /* 0x4C */
    char name[16];              /* 0x50 */
} IOSThread;

/* 16-byte guard word stamped at both ends of a thread stack */
typedef struct { char c[16]; } IosStackMark;

extern IOSThread D_006BD310;    /* the main (boot) IOS thread */
extern char D_006BD380[];       /* its 8 KB stack */
extern int _gp;                 /* linker-defined global pointer */
extern int D_0063A5F0;          /* number of live IOS threads */
extern const char D_00551DB0[16];   /* "<THREAD_SP>...."  */
extern const char D_00551DC0[16];   /* "<THREAD_SP_END>"  */
extern char D_00551DD0[];
extern char D_00551E00[];
extern char D_00551E20[];
extern void iosThreadDestroyMgr();
extern int CreateThread(IOSThread *param);
extern const char D_00551DF0[];
extern char D_0063A5F8[];
extern void debug_assert(const char *file, int line);
extern void __assert(const char *file, int line, const char *expr);

/* MAIN.MAP names iosThreadCreate as a global function and the listing puts
 * its lines 119-155 inside iosThreadInit and iosThreadCreateS, so it is a
 * public `inline` of the deferred tail.  Until every member of that tail is
 * C (iosThreadDestroyMgr and iosThreadAllQuit are still asm) its out-of-line
 * copy stays as the INCLUDE_ASM below and this definition is `static inline`
 * so no second symbol is emitted; the storage class flips at layout time. */
static inline void iosThreadCreate(IOSThread *th, int no, void (*func)(), int arg,
                                   void *stack, long stackSize, int pri)
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

void iosThreadInit(void)
{
    iosThreadCreate(&D_006BD310, 0, iosThreadDestroyMgr, 0, D_006BD380, 0x2000, 13);
    iosThreadStart((int)&D_006BD310);
}
INCLUDE_ASM("asm/nonmatchings/ios/thread", iosThreadCreate);
int iosThreadGetPri(int *a0)
{
    register int **base;  /* s0 */
    if (a0 == 0) {
        int idx;
        base = D_006BCEE0;
        idx = GetThreadId();
        a0 = base[idx];
    }
    return a0[0x18 / 4];
}
extern char D_00551E78[];

int iosGetIOSThreadFromId(unsigned int a0)
{
    int ret;
    if (a0 < 0x101) goto valid;
    debug_StdPrintfDummy(D_00551E78);
    ret = 0;
    goto out;
valid:
    ret = D_006BCEE0[a0];
out:
    return ret;
}
extern int WakeupThread();

int iosThreadWakeup(int *self)
{
    return WakeupThread(self[0x30 / 4]);
}
extern char D_00551EA0[];
extern void iosMsgRecv(void *a, void *b, int c);

int iosThreadJoin(void *a0) {
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

int iosThreadCancelWakeup(int *self)
{
    int v;
    if (self == 0) {
        v = GetThreadId();
    } else {
        v = self[0x30/4];
    }
    return CancelWakeupThread(v);
}
extern int CreateSema(int *self);
extern char D_00551EB8[];
extern char D_0063A5F8[];
extern void __assert(const char *file, int line, const char *expr);
extern void debug_assert(const char *file, int line);

int iosSemaCreate(int *self, int a1, int a2, int a3)
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

int iosSemaDelete(int *self)
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

int iosSemaWait(int *self)
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

int iosSemaSignal(int *self)
{
    int v;
    int rv;
    v = SignalSema(self[0x30 / 4]);
    rv = 0;
    if (v < 0)
    {
        debug_StdPrintfDummy(D_00551F00, self[0x30 / 4]);
        rv = v;
    }
    return rv;
}
extern char D_00551F18[];

int iosSemaReferStatus(int *self)
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
INCLUDE_ASM("asm/nonmatchings/ios/thread", iosThreadDestroyMgr);
INCLUDE_ASM("asm/nonmatchings/ios/thread", iosThreadAllQuit);
