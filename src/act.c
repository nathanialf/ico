#include "common.h"



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
extern void *D_006321DC__p4 __asm__("D_006321DC");

void actCreateMotionThread(void *a0, void *a1, void **a2) {
    void *old = *a2;
    int ret = isysGObjProcPause(D_006321DC__p4, a0, 0, a1);
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

INCLUDE_ASM("asm/nonmatchings/src/act", actInitialize);

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
        char *sub = *(char **)((char *)D_006321DC__p4 + 0x164);
        debug_assertMessage(D_0061AF70, D_006321DC__p4);
        debug_assertMessage(D_0061AF80, *(int *)((char *)D_006321DC__p4 + 8));
        debug_assertMessage(D_0061AF80, *(int *)((char *)D_006321DC__p4 + 0xC));
        if (sub != 0) {
            debug_assertMessage(D_0061AF90, sub);
            debug_assertMessage(D_0061AF80, *(int *)(sub + 0x30));
        }
    }
    r = isysGObjProcPause(D_006321DC__p4, a0, 0, (void *)a1);
    *(int *)(r + 0x64) = 1;
    return r;
}

void actSetInterrupt(char *self, int val) {
    *(int *)(self + 0x0) = val;
}

