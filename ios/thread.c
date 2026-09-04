#include "common.h"

INCLUDE_ASM("asm/nonmatchings/ios/thread", iosThreadMain);
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
INCLUDE_ASM("asm/nonmatchings/ios/thread", iosThreadInit);
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
extern void func_001B6250(const char *file, int line);

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
        func_001B6250(D_00551DF0, 0x25C);
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
        func_001B6250(D_00551DF0, 0x270);
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
        func_001B6250(D_00551DF0, 0x2B0);
        __assert(D_00551DF0, 0x2B0, D_0063A5F8);
        return rv;
    }
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/ios/thread", func_00140018);
