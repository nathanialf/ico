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
INCLUDE_ASM("asm/nonmatchings/ios/thread", iosGetIOSThreadFromId);
extern int WakeupThread();

int iosThreadWakeup(int *self)
{
    return WakeupThread(self[0x30 / 4]);
}
INCLUDE_ASM("asm/nonmatchings/ios/thread", iosThreadJoin);
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
INCLUDE_ASM("asm/nonmatchings/ios/thread", iosSemaCreate);
INCLUDE_ASM("asm/nonmatchings/ios/thread", iosSemaDelete);
INCLUDE_ASM("asm/nonmatchings/ios/thread", iosSemaWait);
INCLUDE_ASM("asm/nonmatchings/ios/thread", iosSemaSignal);
INCLUDE_ASM("asm/nonmatchings/ios/thread", iosSemaReferStatus);
INCLUDE_ASM("asm/nonmatchings/ios/thread", func_00140018);
