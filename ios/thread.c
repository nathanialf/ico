#include "common.h"













extern int D_006A93D0[];
extern void memset();
extern int CancelWakeupThread();
extern int WakeupThread();
extern void ResumeThread();
extern void SuspendThread();
extern void strcpy();
extern void ChangeThreadPriority();
extern char D_006A7330[];
extern int GetThreadId();
extern int iosMsgSend(int *self, int a1, int a2);
extern int D_006A6F30[];
extern void SleepThread();
extern void TerminateThread();
extern void ExitThread();
extern void StartThread();
extern int *D_00632190;
INCLUDE_ASM("asm/nonmatchings/ios/thread", iosThreadMain);

void Init_ShockRequestAlloc(int *a0, char *a1, int a2) {
    if (a0 != 0 && a1 != 0) {
        a0[0] = a2;
        a0[1] = (int)a1;
        if (a2 > 0) {
            do {
                *a1 = 0;
                a1 += 0x40;
            } while (--a2 != 0);
        }
    } else {
        a0[0] = 0;
    }
}

void *iosThreadStart(int *a0) {
    unsigned char *p = (unsigned char *)a0[1];
    int i;
    for (i = 0; i < a0[0]; i++) {
        if (*p == 0) {
            return p;
        }
        p += 0x40;
    }
    return 0;
}

void iosThreadStop(char *p) {
    *p = 0;
}

INCLUDE_ASM("asm/nonmatchings/ios/thread", iosThreadSleep);

INCLUDE_ASM("asm/nonmatchings/ios/thread", iosThreadDestroy);

int Shock_SetShockVoiceSet(int idx, int val)
{
    int *base = (int *)D_00632190;
    int *array;
    if ((unsigned int)idx < (unsigned int)base[0]) goto store;
    idx = -1;
    goto end;
store:
    array = (int *)base[1];
    array[idx] = val;
end:
    return idx;
}

INCLUDE_ASM("asm/nonmatchings/ios/thread", Init_Player);

void iosThreadName(short *a0) {
    a0[1] = 0;
    a0[0] = 0;
}

void iosThreadSuspend(int *self)
{
    int *node = (int *) self[0];
    if (self[0x8 / 4] == 0)
    {
        goto end;
    }
    if (node == 0)
    {
        goto end;
    }
    do
    {
        int *cur = node;
        node = (int *) node[0x34 / 4];
        (*(void (**)(int, int))((char *) self + 8))((int) cur, self[0xC / 4]);
    } while (node != 0);
end:
    self[0] = 0;
}

INCLUDE_ASM("asm/nonmatchings/ios/thread", Shock_Decode);

int iosThreadInit(void)
{
    return 0;
}

void Vibration_SetDecodeEnd(unsigned char *p, int a1, int a2) {
    if (a1) *p &= 0xFE;
    if (a2) *p &= 0xEF;
}

INCLUDE_ASM("asm/nonmatchings/ios/thread", requestFree);

extern void iosThreadSetPri(int *a0, int a1);

void iosGetIOSThreadFromId(int a0)
{
    int idx = GetThreadId();
    int *obj = (int *) D_006A6F30[idx];
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

INCLUDE_ASM("asm/nonmatchings/ios/thread", iosThreadWakeup);

void iosThreadJoin(int a0)
{
    StartThread(*(int *)(a0 + 0x30), *(int *)(a0 + 0x34));
}

void iosThreadCancelWakeup(int a0)
{
    if (a0 == 0) {
        ExitThread();
    } else {
        TerminateThread(*(int *)(a0 + 0x30));
    }
}

void iosSemaCreate(int a0, int a1, int a2, int a3)
{
    SleepThread(a0, a1, a2, a3);
}

void iosSemaDelete(int a0)
{
    int a1 = a0;
    if (a0 == 0) {
        a1 = D_006A6F30[GetThreadId()];
    }
    iosMsgSend(D_006A7330, a1, 0);
}

void iosThreadSetPri(int *a0, int a1)
{
  int *v;
  v = a0;
  if (v == 0)
  {
    v = (int *) D_006A6F30[GetThreadId()];
  }
  else
  {
    v = a0;
  }
  v[0x18 / 4] = a1;
  ChangeThreadPriority(v[0x30 / 4], a1);
}

extern const char D_005578D0[];
extern char D_00557970[];
extern void *D_00632000;
extern extern void debug_StdPrintfDummy();
extern void *func_0013A0F8(void *a, int n, void *c, int d);
extern void iosMsgQueueCreate(void *a, void *b, int c);

void iosThreadMessage(int a0) {
    void *obj = (void *)D_006A6F30[GetThreadId()];
    int q;
    if (*(int *)((char *)obj + 0x48) == 0) {
        void *r;
        *(int *)((char *)obj + 0x48) = 1;
        r = func_0013A0F8(D_00632000, 0x50, (void *)D_005578D0, 0x1DE);
        *(void **)((char *)obj + 0x4C) = r;
        iosMsgQueueCreate(r, (char *)r + 0x30, 8);
    }
    q = iosMsgSend((char *)*(void **)((char *)obj + 0x4C), a0, 0);
    debug_StdPrintfDummy(D_00557970, q);
}

void iosSemaReferStatus(int a0)
{
    strcpy(a0 + 0x50);
}

void iosThreadDestroyMgr(int a0)
{
    SuspendThread(*(int *)(a0 + 0x30));
}

void iosThreadAllQuit(int a0)
{
    ResumeThread(*(int *)(a0 + 0x30));
}

INCLUDE_ASM("asm/nonmatchings/ios/thread", func_0013D550);

INCLUDE_ASM("asm/nonmatchings/ios/thread", func_0013D700);

int iosThreadGetPri(int *a0)
{
    register int **base;  /* s0 */
    if (a0 == 0) {
        int idx;
        base = D_006A6F30;
        idx = GetThreadId();
        a0 = base[idx];
    }
    return a0[0x18 / 4];
}

INCLUDE_ASM("asm/nonmatchings/ios/thread", func_0013D8E0);

int func_0013D928(int *self)
{
    return WakeupThread(self[0x30 / 4]);
}

INCLUDE_ASM("asm/nonmatchings/ios/thread", func_0013D948);

int func_0013D9C8(int *self)
{
    int v;
    if (self == 0) {
        v = GetThreadId();
    } else {
        v = self[0x30/4];
    }
    return CancelWakeupThread(v);
}

INCLUDE_ASM("asm/nonmatchings/ios/thread", func_0013DA00);

INCLUDE_ASM("asm/nonmatchings/ios/thread", func_0013DA88);

INCLUDE_ASM("asm/nonmatchings/ios/thread", iosSemaWait);

INCLUDE_ASM("asm/nonmatchings/ios/thread", iosSemaSignal);

INCLUDE_ASM("asm/nonmatchings/ios/thread", func_0013DBB0);

INCLUDE_ASM("asm/nonmatchings/ios/thread", func_0013DC30);

extern void iosSemaDelete(int a0);

void func_0013DD20(int a0) {
    int i;

    for (i = 0; i < 0x100; i++) {
        if (D_006A6F30[i] != 0 && i != a0) {
            iosSemaDelete((int)D_006A6F30[i]);
        }
    }
}

void func_0013DD88(void)
{
    memset(D_006A93D0, 0, 0x110);
}

