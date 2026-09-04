#include "common.h"

extern void debug_StdPrintfDummy();
extern void isysGObjProcAddS();
extern int actCreateSubThread(void *a0, int a1);
extern char D_00613A70[];
extern char D_00613A90[];

void actChangeActBrain(void *a0, void *a1, void **a2) {
    void *old = *a2;
    int ret = actCreateSubThread(a1, 0x14);
    *a2 = (void *)ret;
    if (old != 0) {
        debug_StdPrintfDummy(D_00613A70, a0, ret);
        isysGObjProcAddS(old);
    } else {
        debug_StdPrintfDummy(D_00613A90, a0, ret);
    }
}

extern int isysGObjProcPause(void *a0, void *a1, int a2, void *a3);
extern int isysGObjProcPauseAll(void *a0, void *a1, int a2, void *a3, long long a4);
extern char D_002A0A90[];
extern char D_00613AB0[];
extern char D_00613AD0[];

void actChangeActMain(void *a0, void *a1, void **a2) {
    char *e = D_002A0A90 + *(int *)((char *)a0 + 8) * 0x4C;
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
        debug_StdPrintfDummy(D_00613AB0, a0, ret);
        isysGObjProcAddS(old);
    } else {
        debug_StdPrintfDummy(D_00613AD0, a0, ret);
    }
}


extern void debug_StdPrintfDummy();
extern void isysGObjProcAddS();
extern int isysGObjProcPause(void *a0, void *a1, int a2, void *a3);
extern void *D_0062A4DC;
extern char D_00613AF0[];
extern char D_00613B10[];

void actCreateMotionThread(void *a0, void *a1, void **a2) {
    void *old = *a2;
    int ret = isysGObjProcPause(D_0062A4DC, a0, 0, a1);
    *a2 = (void *)ret;
    if (old != 0) {
        debug_StdPrintfDummy(D_00613AF0, *(int *)((char *)old + 4), ret);
        isysGObjProcAddS(old);
    } else {
        debug_StdPrintfDummy(D_00613B10, ret, ret);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", after_func_exec);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", actInitialize_ext_charcter);

extern int iosFree(int, int, const char *, int);
extern void memset(void *, int, int);
extern int D_0062A324;
extern int D_0062A4E0;
extern char D_00613B60[];
extern char D_0027D340[];

typedef union {
    struct { int lo; int hi; } w;
    long long ll;
} CondU;

char *actInitialize(char *obj)
{
    char *s;
    long long f;
    long long g;

    s = (char *)iosFree(D_0062A324, 0x840, D_00613B60, 0x37C);
    *(char **)(obj + 0x164) = s;
    memset(s, 0, 0x840);

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

    *(int *)(s + 0x4) = D_0062A4E0;
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
    *(int *)(s + 0xB0) = 0;
    *(int *)(s + 0xB4) = 0;
    *(int *)(s + 0x110) = 0;
    *(int *)(s + 0x11C) = 0;
    *(int *)(s + 0x128) = 0;
    *(int *)(s + 0x12C) = 0;
    *(int *)(s + 0x130) = 0;
    *(int *)(s + 0x134) = 0;
    *(int *)(s + 0x430) = 0;
    *(int *)(s + 0x434) = 0;
    *(int *)(s + 0x438) = 0;
    *(int *)(s + 0x43C) = 0;
    *(int *)(s + 0x50) = 0;
    g = ((CondU *)(s + 0x20))->ll;
    g |= 0x200;
    g &= ~0x400;
    g |= 0x2000;
    g |= 0x80000;
    ((CondU *)(s + 0x20))->ll = g;
    *(int *)(s + 0x3B4) = -1;
    *(int *)(s + 0x394) = 0;

    {
        int t = *(int *)(obj + 0x164);
        *(int *)(t + 0x1A0) = 0;
        *(char *)(t + 0x1CA) = 0;
    }

    __builtin_memcpy(s + 0x1D8, D_0027D340, 0xF0);

    memset(s + 0x150, 0, 0x20);
    memset(s + 0x114, 0, 8);
    memset(s + 0x180, 0, 0x20);
    memset(s + 0x46C, 0, 0x10);
    memset(s + 0x47C, 0, 0x10);
    memset(s + 0x48C, 0, 0x10);
    memset(s + 0x4A0, 0, 0x1D0);
    memset(s + 0x2C8, 0, 0x60);
    memset(s + 0x328, 0, 0x18);
    return s;
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", act_check_intr_list);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", act_check_mail);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", BeforeFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", ACTDebugMove);

void actInitialize_geo(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", actInitialize_only_charcter);

extern int iosOmSendMail(void *self, int val5, int val6);

int ACTReserveTarget(void *a0, int a1, int a2)
{
    char *s = *(char **)((char *)a0 + 0x164);
    if (*(int *)(s + 0x11C) == 0) {
        *(void **)(s + 0x11C) = a0;
        *(int *)(s + 0x120) = a2;
        iosOmSendMail(a0, a2, a1);
        return 1;
    }
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

extern int D_00271240[];
extern void iosSemaCreate(void);

void _ACTWait(int a0) {
    int count = (a0 * ((0x3C - D_00271240[0] * 0xA) / D_00271240[1])) / 0x3C;
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

extern void *D_0062A4DC;
extern void *isysGObjProcPausePtr(void *a0, void *a1, int a2, void *a3);

void actCreateSubThreadGOppArg(void *a0, void *a1) {
    void *p = isysGObjProcPausePtr(D_0062A4DC, a0, 0, a1);
    *(int *)((char *)p + 0x64) = 1;
}

extern int D_0062B050;
extern void *D_0062A4DC;
extern char D_00613B30[];
extern char D_00613B40[];
extern char D_00613B50[];
extern int isysGObjProcPause(void *a0, void *a1, int a2, void *a3);

int actCreateSubThread(void *a0, int a1) {
    int r;
    if (D_0062B050 != 0) {
        char *sub = *(char **)((char *)D_0062A4DC + 0x164);
        debug_StdPrintfDummy(D_00613B30, D_0062A4DC);
        debug_StdPrintfDummy(D_00613B40, *(int *)((char *)D_0062A4DC + 8));
        debug_StdPrintfDummy(D_00613B40, *(int *)((char *)D_0062A4DC + 0xC));
        if (sub != 0) {
            debug_StdPrintfDummy(D_00613B50, sub);
            debug_StdPrintfDummy(D_00613B40, *(int *)(sub + 0x30));
        }
    }
    r = isysGObjProcPause(D_0062A4DC, a0, 0, (void *)a1);
    *(int *)(r + 0x64) = 1;
    return r;
}

void actSetInterrupt(int *a0, int a1) {
    *a0 = a1;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4C;  /* 0x4C */
} S_00557188;  /* stride 0x50 */

/* end struct shapes */
