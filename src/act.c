#include "common.h"

typedef union {
    struct { int lo; int hi; } w;
    long long ll;
} CondU;



extern char *D_006321DC;
extern int isysGObjProcPausePtr();
extern int iosOmBeforeFuncStandard(char *self_arg, int val5, int val6);
INCLUDE_ASM("asm/nonmatchings/src/act", actChangeActBrain);

extern char D_002A4C48[];
extern char D_0061AEF0[];
extern char D_0061AF10[];
extern void debug_assertMessage();
extern void isysGObjProcAddS();
extern int isysGObjProcPause(void *a0, void *a1, int a2, void *a3);
extern int isysGObjProcPauseAll(void *a0, void *a1, int a2, void *a3, long long a4);

void actChangeActMain(void *a0, void *a1, void **a2) {
    char *e = D_002A4C48 + *(int *)((char *)a0 + 8) * 0x4C;
    unsigned short fld = *(unsigned short *)(e + 0x40);
    void *old = *a2;
    int ret;
    if (((long long) fld << 10) == 0) {
        ret = isysGObjProcPause(a0, a1, 0, (void *)0x13);
    } else {
        ret = isysGObjProcPauseAll(a0, a1, 0, (void *)0x13, (long long) fld << 10);
    }
    *a2 = (void *)ret;
    if (old != 0) {
        debug_assertMessage(D_0061AEF0, a0, ret);
        isysGObjProcAddS(old);
    } else {
        debug_assertMessage(D_0061AF10, a0, ret);
    }
}

extern char D_0061AF30[];
extern char D_0061AF50[];

void actCreateMotionThread(void *a0, void *a1, void **a2) {
    void *old = *a2;
    int ret = isysGObjProcPause(D_006321DC, a0, 0, a1);
    *a2 = (void *)ret;
    if (old != 0) {
        debug_assertMessage(D_0061AF30, *(int *)((char *)old + 4), ret);
        isysGObjProcAddS(old);
    } else {
        debug_assertMessage(D_0061AF50, ret, ret);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/act", after_func_exec);

INCLUDE_ASM("asm/nonmatchings/src/act", actInitialize_ext_charcter);

extern char D_00280FC0[];
extern char D_0061AFA0[];
extern int D_00632024;
extern int D_006321E0;
extern int func_0013A0F8(int, int, const char *, int);
extern void func_002641D8(void *, int, int);

char *actInitialize(char *obj)
{
    char *s;
    long long f;
    long long g;

    s = (char *)func_0013A0F8(D_00632024, 0x840, D_0061AFA0, 0x382);
    *(char **)(obj + 0x164) = s;
    func_002641D8(s, 0, 0x840);

    ((CondU *)(s + 0x18))->w.lo = 0;
    ((CondU *)(s + 0x20))->w.hi = 0;

    f = ((CondU *)(s + 0x18))->ll;
    f |= (long long)0x8000 << 17;
    f |= (long long)0x8000 << 18;
    f &= ~((long long)0x8 << 32);
    f &= ~((long long)0x10 << 32);
    f |= (long long)0x8000 << 23;
    f &= ~((long long)0x80 << 32);
    f |= (long long)0x8000 << 26;
    f &= ~((long long)0x400 << 32);
    f |= (long long)0x8000 << 28;
    f |= (long long)0x8000 << 29;
    f &= ~((long long)0x4000 << 32);
    f &= ~((long long)0x8000 << 32);
    ((CondU *)(s + 0x18))->ll = f;

    *(int *)(s + 0x4) = D_006321E0;
    *(int *)(s + 0x0) = 0;
    *(int *)(s + 0x8) = 0;
    *(int *)(s + 0xC) = 0;
    *(int *)(s + 0x14) = 0;
    *(int *)(s + 0x670) = 0;
    *(int *)(s + 0x678) = 0;
    *(int *)(s + 0x10) = 0;
    *(int *)(s + 0x30) = 0;
    *(int *)(s + 0x34) = 0;
    *(int *)(s + 0x48) = 0;
    *(int *)(s + 0x340) = 0;
    *(int *)(s + 0x37C) = 0;
    *(int *)(s + 0x3C4) = 0;
    *(int *)(s + 0x44) = -1;
    *(int *)(s + 0xC0) = 0;
    *(int *)(s + 0xC4) = 0;
    *(int *)(s + 0x120) = 0;
    *(int *)(s + 0x12C) = 0;
    *(int *)(s + 0x138) = 0;
    *(int *)(s + 0x13C) = 0;
    *(int *)(s + 0x140) = 0;
    *(int *)(s + 0x144) = 0;
    *(int *)(s + 0x430) = 0;
    *(int *)(s + 0x434) = 0;
    *(int *)(s + 0x438) = 0;
    *(int *)(s + 0x43C) = 0;
    *(int *)(s + 0x50) = 0;
    g = ((CondU *)(s + 0x20))->ll;
    g |= 0x1000;
    g &= ~0x2000;
    g |= 0x10000;
    g |= 0x4000000;
    ((CondU *)(s + 0x20))->ll = g;
    *(int *)(s + 0x3B4) = -1;
    *(int *)(s + 0x394) = 0;

    {
        int t = *(int *)(obj + 0x164);
        *(int *)(t + 0x1A0) = 0;
        *(char *)(t + 0x1CA) = 0;
    }

    __builtin_memcpy(s + 0x1D8, D_00280FC0, 0xF0);

    func_002641D8(s + 0x160, 0, 0x20);
    func_002641D8(s + 0x124, 0, 8);
    func_002641D8(s + 0x180, 0, 0x20);
    func_002641D8(s + 0x46C, 0, 0x10);
    func_002641D8(s + 0x47C, 0, 0x10);
    func_002641D8(s + 0x48C, 0, 0x10);
    func_002641D8(s + 0x4A0, 0, 0x1D0);
    func_002641D8(s + 0x2C8, 0, 0x60);
    func_002641D8(s + 0x328, 0, 0x18);
    return s;
}

INCLUDE_ASM("asm/nonmatchings/src/act", act_check_intr_list);

INCLUDE_ASM("asm/nonmatchings/src/act", act_check_mail);

INCLUDE_ASM("asm/nonmatchings/src/act", BeforeFunc);

INCLUDE_ASM("asm/nonmatchings/src/act", ACTDebugMove);

void actInitialize_geo(void) {}

INCLUDE_ASM("asm/nonmatchings/src/act", actInitialize_only_charcter);

int ACTReserveTarget(int *self, int a1, int a2)
{
    int *p = (int *)self[0x164 / 4];
    if (p[0x12C / 4] != 0)
        goto ret0;
    p[0x12C / 4] = (int)self;
    p[0x130 / 4] = a2;
    iosOmBeforeFuncStandard(self, a2, a1);
    return 1;
ret0:
    return 0;
}

extern void iosSemaCreate(void);

void _ACTRun(int n) {
    int i;
    if (n == 0) {
        for (;;) {
            iosSemaCreate();
        }
    }
    if (n > 0) {
        i = n;
        do {
            iosSemaCreate();
            i--;
        } while (i != 0);
    }
}

extern int D_00274EC0[];

void _ACTWait(int a0) {
    int count = (a0 * ((0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1])) / 0x3C;
    if (a0 != 0) {
        if (count == 0) {
            count = 1;
        }
    }
    if (count == 0) {
        for (;;) {
            iosSemaCreate();
        }
    }
    if (count > 0) {
        int i = count;
        do {
            iosSemaCreate();
            i--;
        } while (i != 0);
    }
}

void actCreateSubThreadGOppArg(int a0, int a1)
{
    *(int *)((char *)isysGObjProcPausePtr(D_006321DC, a0, 0, a1) + 0x64) = 1;
}

extern char D_0061AF70[];
extern char D_0061AF80[];
extern char D_0061AF90[];
extern int D_00632D88;

int actCreateSubThread(void *a0, int a1) {
    int r;
    if (D_00632D88 != 0) {
        char *sub = *(char **)((char *)D_006321DC + 0x164);
        debug_assertMessage(D_0061AF70, D_006321DC);
        debug_assertMessage(D_0061AF80, *(int *)((char *)D_006321DC + 8));
        debug_assertMessage(D_0061AF80, *(int *)((char *)D_006321DC + 0xC));
        if (sub != 0) {
            debug_assertMessage(D_0061AF90, sub);
            debug_assertMessage(D_0061AF80, *(int *)(sub + 0x30));
        }
    }
    r = isysGObjProcPause(D_006321DC, a0, 0, (void *)a1);
    *(int *)(r + 0x64) = 1;
    return r;
}

void actSetInterrupt(char *self, int val) {
    *(int *)(self + 0x0) = val;
}

