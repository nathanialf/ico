#include "common.h"

extern void debug_assertMessage();
extern void isysGObjProcAddS();
extern int actCreateSubThread(void *a0, int a1);
extern char D_00613A70[];
extern char D_00613A90[];

void actChangeActBrain(void *a0, void *a1, void **a2) {
    void *old = *a2;
    int ret = actCreateSubThread(a1, 0x14);
    *a2 = (void *)ret;
    if (old != 0) {
        debug_assertMessage(D_00613A70, a0, ret);
        isysGObjProcAddS(old);
    } else {
        debug_assertMessage(D_00613A90, a0, ret);
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
        debug_assertMessage(D_00613AB0, a0, ret);
        isysGObjProcAddS(old);
    } else {
        debug_assertMessage(D_00613AD0, a0, ret);
    }
}


extern void debug_assertMessage();
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
        debug_assertMessage(D_00613AF0, *(int *)((char *)old + 4), ret);
        isysGObjProcAddS(old);
    } else {
        debug_assertMessage(D_00613B10, ret, ret);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", after_func_exec);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", actInitialize_ext_charcter);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", actInitialize);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", act_check_intr_list);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", act_check_mail);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", BeforeFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", ACTDebugMove);

void actInitialize_geo(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", actInitialize_only_charcter);

extern int iosOmBeforeFuncStandard(void *self, int val5, int val6);

int ACTReserveTarget(void *a0, int a1, int a2)
{
    char *s = *(char **)((char *)a0 + 0x164);
    if (*(int *)(s + 0x11C) == 0) {
        *(void **)(s + 0x11C) = a0;
        *(int *)(s + 0x120) = a2;
        iosOmBeforeFuncStandard(a0, a2, a1);
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
        debug_assertMessage(D_00613B30, D_0062A4DC);
        debug_assertMessage(D_00613B40, *(int *)((char *)D_0062A4DC + 8));
        debug_assertMessage(D_00613B40, *(int *)((char *)D_0062A4DC + 0xC));
        if (sub != 0) {
            debug_assertMessage(D_00613B50, sub);
            debug_assertMessage(D_00613B40, *(int *)(sub + 0x30));
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
