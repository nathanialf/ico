#include "common.h"

extern void SleepThread(void);
extern void SuspendThread(void *a0);
extern void ResumeThread(void *a0);
extern void strcpy(void *a0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadMain);

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

void iosThreadStop(unsigned char *a0) {
    *a0 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadSleep);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadDestroy);

extern int *D_0062A490;

int Shock_SetShockVoiceSet(int a0, int a1) {
    int *p = D_0062A490;
    if ((unsigned int)a0 < (unsigned int)p[0]) goto store;
    a0 = -1;
    goto end;
store:
    ((int *)p[1])[a0] = a1;
end:
    return a0;
}

extern int iosThreadInit(void);
extern int D_0062A4A8;

void Init_Player(int *a0)
{
    void (*fn1)(void) = (void (*)(void))iosThreadStart;
    void (*fn2)(void) = (void (*)(void)) iosThreadStop;
    a0[0] = 0;
    if (fn1 != 0) {
        a0[1] = (int)fn1;
    } else {
        a0[1] = (int)iosThreadInit;
    }
    a0[2] = (int)fn2;
    a0[3] = (int)&D_0062A4A8;
}

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", Shock_Decode);

int iosThreadInit(void) {
    return 0;
}

void Vibration_SetDecodeEnd(unsigned char *a0, int a1, int a2) {
    if (a1) {
        a0[0] &= 0xFE;
    }
    if (a2) {
        a0[0] &= 0xEF;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", requestFree);

extern int D_006A0AB0[];
extern int GetThreadId(void);

void iosGetIOSThreadFromId(int a0)
{
    int idx = GetThreadId();
    int *obj = (int *) D_006A0AB0[idx];
    (*(void (**)(int))((char *) obj + 0x38))(a0);
    if (*(int *)((char *) obj + 0x40) == 0)
    {
        iosThreadSetPri(obj, 0x21);
    }
    else
    {
        iosThreadSetPri(obj, 0x22);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadWakeup);

extern void StartThread(void *a0, int a1);

void iosThreadJoin(int *a0) {
    StartThread((void *)a0[0xC], a0[0xD]);
}

extern void ExitThread(void);
extern void TerminateThread(void *a0);

void iosThreadCancelWakeup(void *a0) {
    if (a0 == 0) {
        ExitThread();
        return;
    }
    TerminateThread(*(void **)((char *)a0 + 0x30));
}

void iosSemaCreate(void) {
    SleepThread();
}

extern char D_006A0EB0[];
extern int iosMsgSend(char *a, int b, int c);

void iosSemaDelete(int a0)
{
    int a1 = a0;
    if (a0 == 0) {
        a1 = D_006A0AB0[GetThreadId()];
    }
    iosMsgSend(D_006A0EB0, a1, 0);
}

extern void ChangeThreadPriority(int a, int b);

void iosThreadSetPri(int *a0, int a1)
{
  int *v;
  v = a0;
  if (v == 0)
  {
    v = (int *) D_006A0AB0[GetThreadId()];
  }
  else
  {
    v = a0;
  }
  v[0x18 / 4] = a1;
  ChangeThreadPriority(v[0x30 / 4], a1);
}

extern int GetThreadId(void);
extern void *iosFree(void *a, int n, void *c, int d);
extern void iosMsgQueueDestroy(void *a, void *b, int c);
extern void debug_StdPrintfDummy();
extern void *D_0062A300;
extern const char D_00551CA0[];
extern char D_00551D40[];
void iosThreadMessage(int a0) {
    void *obj = (void *)D_006A0AB0[GetThreadId()];
    int q;
    if (*(int *)((char *)obj + 0x48) == 0) {
        void *r;
        *(int *)((char *)obj + 0x48) = 1;
        r = iosFree(D_0062A300, 0x50, (void *)D_00551CA0, 0x1DE);
        *(void **)((char *)obj + 0x4C) = r;
        iosMsgQueueDestroy(r, (char *)r + 0x30, 8);
    }
    q = iosMsgSend((char *)*(void **)((char *)obj + 0x4C), a0, 0);
    debug_StdPrintfDummy(D_00551D40, q);
}

void iosSemaReferStatus(void *a0) {
    strcpy((char *)a0 + 0x50);
}

void iosThreadDestroyMgr(void *a0) {
    SuspendThread(*(void **)((char *)a0 + 0x30));
}

void iosThreadAllQuit(void *a0) {
    ResumeThread(*(void **)((char *)a0 + 0x30));
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D038);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D1E8);

int iosThreadGetPri(int *a0)
{
    register int **base;  /* s0 */
    if (a0 == 0) {
        int idx;
        base = D_006A0AB0;
        idx = GetThreadId();
        a0 = base[idx];
    }
    return a0[0x18 / 4];
}

extern void debug_StdPrintfDummy();

extern char D_00551D28[];

int func_0013D3C8(unsigned int a0)
{
    int ret;
    if (a0 < 0x101) goto valid;
    debug_StdPrintfDummy(D_00551D28);
    ret = 0;
    goto out;
valid:
    ret = D_006A0AB0[a0];
out:
    return ret;
}

extern int WakeupThread(void *a0);

int func_0013D410(void *a0) {
    return WakeupThread(*(void **)((char *)a0 + 0x30));
}

extern void *iosFree(void *a, int n, void *c, int d);
extern void iosMsgQueueDestroy(void *a, void *b, int c);
extern void iosMsgRecv(void *a, void *b, int c);
extern void debug_StdPrintfDummy();
extern void *D_0062A300;
extern const char D_00551CA0[];
extern char D_00551D50[];
int func_0013D430(void *a0) {
    int buf[4];
    if (*(int *)((char *)a0 + 0x48) == 0) {
        void *r;
        *(int *)((char *)a0 + 0x48) = 1;
        r = iosFree(D_0062A300, 0x50, (void *)D_00551CA0, 0x1FA);
        *(void **)((char *)a0 + 0x4C) = r;
        iosMsgQueueDestroy(r, (char *)r + 0x30, 8);
    }
    iosMsgRecv(*(void **)((char *)a0 + 0x4C), buf, 1);
    debug_StdPrintfDummy(D_00551D50);
    return buf[0];
}

extern int GetThreadId(void);
extern int CancelWakeupThread(int a0);

int func_0013D4B0(void *a0) {
    int id;
    if (a0 == 0) {
        id = GetThreadId();
    } else {
        id = *(int *)((char *)a0 + 0x30);
    }
    return CancelWakeupThread(id);
}

extern const char D_00551CA0[];
extern int CreateSema(int *self);
extern char D_0062C338[];
extern void func_001AAD00(const char *file, int line);
extern void __assert(const char *file, int line, const char *expr);

extern char D_00551D68[];

int func_0013D4E8(int *self, int a1, int a2, int a3)
{
    int rv;
    self[0x8 / 4] = a1;
    self[0x4 / 4] = a2;
    self[0x14 / 4] = a3;
    rv = CreateSema(self);
    self[0x30 / 4] = rv;
    if (rv < 0) {
        debug_StdPrintfDummy(D_00551D68, rv);
        func_001AAD00(D_00551CA0, 0x25C);
        __assert(D_00551CA0, 0x25C, D_0062C338);
        return self[0x30 / 4];
    }
    return 0;
}

extern int DeleteSema(int sem);

extern char D_00551D80[];

int func_0013D570(int *self)
{
    int rv = DeleteSema(self[0x30 / 4]);
    if (rv < 0) {
        debug_StdPrintfDummy(D_00551D80, self[0x30 / 4]);
        func_001AAD00(D_00551CA0, 0x270);
        __assert(D_00551CA0, 0x270, D_0062C338);
        return rv;
    }
    return 0;
}

extern int ReferSemaStatus(int sem, int *self);
extern int WaitSema(int sem);

extern char D_00551D98[];

int iosSemaWait(int *self)
{
    int rv = ReferSemaStatus(self[0x30 / 4], self);
    if (rv < 0) {
        debug_StdPrintfDummy(D_00551D98, self[0x30 / 4]);
        return rv;
    }
    WaitSema(self[0x30 / 4]);
    return 0;
}

extern int SignalSema(int x);

extern char D_00551DB0[];

int iosSemaSignal(int *self)
{
    int v;
    int rv;
    v = SignalSema(self[0x30 / 4]);
    rv = 0;
    if (v < 0)
    {
        debug_StdPrintfDummy(D_00551DB0, self[0x30 / 4]);
        rv = v;
    }
    return rv;
}

extern char D_00551DC8[];

int func_0013D698(int *self)
{
    int rv = ReferSemaStatus(self[0x30 / 4], self + 0x18 / 4);
    if (rv < 0) {
        debug_StdPrintfDummy(D_00551DC8, self[0x30 / 4]);
        func_001AAD00(D_00551CA0, 0x2B0);
        __assert(D_00551CA0, 0x2B0, D_0062C338);
        return rv;
    }
    return 0;
}

extern int iosMallocCheckLeak2(int a0);
extern int send_signal_message(int a0);
extern char D_00551CF8[];
extern char D_00551D18[];
extern int D_0062A4B0;
extern int D_0062BFA0;
extern char D_006A0EB0[];
extern int D_006A0AB0[];
extern void DeleteThread(int a0);

typedef struct ThreadMsg {
    int pad0[12];
    int f30;
    int pad34[2];
    int f3C;
    int pad40[2];
    int f48;
    int f4C;
} ThreadMsg;

void func_0013D718(void)
{
  unsigned char new_var;
  int one = 1;
  int id;
  ThreadMsg *msg;
  debug_StdPrintfDummy(D_00551CF8);
  iosMsgQueueDestroy(D_006A0EB0, &D_0062BFA0, 2);
  for (;;)
  {
    iosMsgRecv(D_006A0EB0, &msg, 1);
    id = msg->f30;
    D_0062A4B0 -= 1;
    debug_StdPrintfDummy(D_00551D18, D_0062A4B0);
    TerminateThread((void *) id);
    DeleteThread(id);
    new_var = one;
    if ((msg->f3C & 1) == new_var)
    {
      iosMallocCheckLeak2(((int *) D_006A0AB0[id])[0x8 / 4]);
    }
    if (msg->f48 != 0)
    {
      send_signal_message(msg->f4C);
      iosMallocCheckLeak2(msg->f4C);
    }
    D_006A0AB0[id] = 0;
  }

}



void func_0013D808(int a0) {
    int i;

    for (i = 0; i < 0x100; i++) {
        if (D_006A0AB0[i] != 0 && i != a0) {
            iosSemaDelete(D_006A0AB0[i]);
        }
    }
}


extern unsigned char D_006A2F50[];
extern void memset(void *a0, int a1, int a2);

void func_0013D870(void) {
    memset(D_006A2F50, 0, 0x10C);
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
    unsigned int       f_14;  /* 0x14 */
    unsigned int       f_18;  /* 0x18 */
    unsigned int       f_30;  /* 0x30 */
    unsigned int       f_34;  /* 0x34 */
    unsigned int       f_38;  /* 0x38 */
    unsigned int       f_40;  /* 0x40 */
} S_006A0EE0;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_006A0AB0;  /* stride 0x4 */

/* end struct shapes */
