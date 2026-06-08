#include "common.h"

extern void func_00100440(void);
extern void func_00100490(void *a0);
extern void func_001004B0(void *a0);
extern void func_002614F8(void *a0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadMain);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadCreateS);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadStart);

void iosThreadStop(unsigned char *a0) {
    *a0 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadSleep);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadDestroy);

extern int *D_0062A490;

int iosThreadSetPri(int a0, int a1) {
    int *p = D_0062A490;
    if ((unsigned int)a0 < (unsigned int)p[0]) goto store;
    a0 = -1;
    goto end;
store:
    ((int *)p[1])[a0] = a1;
end:
    return a0;
}

extern void iosThreadStart(void);
extern int iosThreadInit(void);
extern int D_0062A4A8;

void iosThreadMessage(int *a0)
{
    void (*fn1)(void) = iosThreadStart;
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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadResume);

int iosThreadInit(void) {
    return 0;
}

void iosThreadCreate(unsigned char *a0, int a1, int a2) {
    if (a1) {
        a0[0] &= 0xFE;
    }
    if (a2) {
        a0[0] &= 0xEF;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadGetPri);

extern int D_006A0AB0[];
extern int func_00100410(void);

void iosGetIOSThreadFromId(int a0)
{
    int idx = func_00100410();
    int *obj = (int *) D_006A0AB0[idx];
    (*(void (**)(int))((char *) obj + 0x38))(a0);
    if (*(int *)((char *) obj + 0x40) == 0)
    {
        iosSemaWait(obj, 0x21);
    }
    else
    {
        iosSemaWait(obj, 0x22);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadWakeup);

extern void func_00100340(void *a0, int a1);

void iosThreadJoin(int *a0) {
    func_00100340((void *)a0[0xC], a0[0xD]);
}

extern void func_00100350(void);
extern void func_00100370(void *a0);

void iosThreadCancelWakeup(void *a0) {
    if (a0 == 0) {
        func_00100350();
        return;
    }
    func_00100370(*(void **)((char *)a0 + 0x30));
}

void iosSemaCreate(void) {
    func_00100440();
}

extern char D_006A0EB0[];
extern int iosMsgSend(char *a, int b, int c);

void iosSemaDelete(int a0)
{
    int a1 = a0;
    if (a0 == 0) {
        a1 = D_006A0AB0[func_00100410()];
    }
    iosMsgSend(D_006A0EB0, a1, 0);
}

extern void func_001003B0(int a, int b);

void iosSemaWait(int *a0, int a1)
{
  int *v;
  v = a0;
  if (v == 0)
  {
    v = (int *) D_006A0AB0[func_00100410()];
  }
  else
  {
    v = a0;
  }
  v[0x18 / 4] = a1;
  func_001003B0(v[0x30 / 4], a1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosSemaSignal);

void iosSemaReferStatus(void *a0) {
    func_002614F8((char *)a0 + 0x50);
}

void iosThreadDestroyMgr(void *a0) {
    func_00100490(*(void **)((char *)a0 + 0x30));
}

void iosThreadAllQuit(void *a0) {
    func_001004B0(*(void **)((char *)a0 + 0x30));
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D038);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D1E8);

int func_0013D388(int *a0)
{
    register int **base;  /* s0 */
    if (a0 == 0) {
        int idx;
        base = D_006A0AB0;
        idx = func_00100410();
        a0 = base[idx];
    }
    return a0[0x18 / 4];
}

extern void debug_assertMessage();

extern char D_00551D28[];

int func_0013D3C8(unsigned int a0)
{
    int ret;
    if (a0 < 0x101) goto valid;
    debug_assertMessage(D_00551D28);
    ret = 0;
    goto out;
valid:
    ret = D_006A0AB0[a0];
out:
    return ret;
}

extern int func_00100450(void *a0);

int func_0013D410(void *a0) {
    return func_00100450(*(void **)((char *)a0 + 0x30));
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D430);

extern int func_00100410(void);
extern int func_00100470(int a0);

int func_0013D4B0(void *a0) {
    int id;
    if (a0 == 0) {
        id = func_00100410();
    } else {
        id = *(int *)((char *)a0 + 0x30);
    }
    return func_00100470(id);
}

extern const char D_00551CA0[];
extern int func_00100520(int *self);
extern char D_0062C338[];
extern void func_001AAD00(const char *file, int line);
extern void func_00260380(const char *file, int line, const char *expr);

extern char D_00551D68[];

int func_0013D4E8(int *self, int a1, int a2, int a3)
{
    int rv;
    self[0x8 / 4] = a1;
    self[0x4 / 4] = a2;
    self[0x14 / 4] = a3;
    rv = func_00100520(self);
    self[0x30 / 4] = rv;
    if (rv < 0) {
        debug_assertMessage(D_00551D68, rv);
        func_001AAD00(D_00551CA0, 0x25C);
        func_00260380(D_00551CA0, 0x25C, D_0062C338);
        return self[0x30 / 4];
    }
    return 0;
}

extern int func_00100530(int sem);

extern char D_00551D80[];

int func_0013D570(int *self)
{
    int rv = func_00100530(self[0x30 / 4]);
    if (rv < 0) {
        debug_assertMessage(D_00551D80, self[0x30 / 4]);
        func_001AAD00(D_00551CA0, 0x270);
        func_00260380(D_00551CA0, 0x270, D_0062C338);
        return rv;
    }
    return 0;
}

extern int func_00100590(int sem, int *self);
extern int func_00100560(int sem);

extern char D_00551D98[];

int func_0013D5E8(int *self)
{
    int rv = func_00100590(self[0x30 / 4], self);
    if (rv < 0) {
        debug_assertMessage(D_00551D98, self[0x30 / 4]);
        return rv;
    }
    func_00100560(self[0x30 / 4]);
    return 0;
}

extern int func_00100540(int x);

extern char D_00551DB0[];

int func_0013D648(int *self)
{
    int v;
    int rv;
    v = func_00100540(self[0x30 / 4]);
    rv = 0;
    if (v < 0)
    {
        debug_assertMessage(D_00551DB0, self[0x30 / 4]);
        rv = v;
    }
    return rv;
}

extern char D_00551DC8[];

int func_0013D698(int *self)
{
    int rv = func_00100590(self[0x30 / 4], self + 0x18 / 4);
    if (rv < 0) {
        debug_assertMessage(D_00551DC8, self[0x30 / 4]);
        func_001AAD00(D_00551CA0, 0x2B0);
        func_00260380(D_00551CA0, 0x2B0, D_0062C338);
        return rv;
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D718);

extern unsigned char D_006A2F50[];
extern void func_00260568(void *a0, int a1, int a2);

void func_0013D870(void) {
    func_00260568(D_006A2F50, 0, 0x10C);
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
