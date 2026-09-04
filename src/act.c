#include "common.h"

typedef union { float f[4]; long long ll[2]; } Vec4;

extern char D_00621BB0[];
extern char D_00621BD0[];
void actChangeActBrain(int a0, int a1, int *a2) {
    int old = *a2;
    int n = actCreateSubThread(a1, 0x14);
    *a2 = n;
    if (old != 0) {
        debug_StdPrintfDummy(D_00621BB0, a0, n);
        isysGObjProcRemove(old);
    } else {
        debug_StdPrintfDummy(D_00621BD0, a0, n);
    }
}
extern char D_002C2DC8[];
extern char D_00621BF0[];
extern char D_00621C10[];
extern void debug_StdPrintfDummy();
extern int isysGObjProcAdd(void *a0, void *a1, int a2, void *a3);
extern int isysGObjProcAddS(void *a0, void *a1, int a2, void *a3, long long a4);
extern void isysGObjProcRemove();

void actChangeActMain(void *a0, void *a1, void **a2) {
    char *e = D_002C2DC8 + *(int *)((char *)a0 + 8) * 0x4C;
    unsigned short fld = *(unsigned short *)(e + 0x40);
    void *old = *a2;
    int ret;
    if (((long long) fld << 10) == 0) {
        ret = isysGObjProcAdd(a0, a1, 0, (void *)0x13);
    } else {
        ret = isysGObjProcAddS(a0, a1, 0, (void *)0x13, (long long) fld << 10);
    }
    *a2 = (void *)ret;
    if (old != 0) {
        debug_StdPrintfDummy(D_00621BF0, a0, ret);
        isysGObjProcRemove(old);
    } else {
        debug_StdPrintfDummy(D_00621C10, a0, ret);
    }
}
extern char D_00621C30[];
extern char D_00621C50[];
extern char *D_0063A61C;

void actCreateMotionThread(void *a0, void *a1, void **a2) {
    void *old = *a2;
    int ret = isysGObjProcAdd(D_0063A61C, a0, 0, a1);
    *a2 = (void *)ret;
    if (old != 0) {
        debug_StdPrintfDummy(D_00621C30, *(int *)((char *)old + 4), ret);
        isysGObjProcRemove(old);
    } else {
        debug_StdPrintfDummy(D_00621C50, ret, ret);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/act", actCreateSubThread);
INCLUDE_ASM("asm/nonmatchings/src/act", after_func_exec);
INCLUDE_ASM("asm/nonmatchings/src/act", actInitialize_ext_charcter);
INCLUDE_ASM("asm/nonmatchings/src/act", actInitialize_only_charcter);
INCLUDE_ASM("asm/nonmatchings/src/act", actInitialize);
INCLUDE_ASM("asm/nonmatchings/src/act", act_check_intr_list);
INCLUDE_ASM("asm/nonmatchings/src/act", act_check_mail);
INCLUDE_ASM("asm/nonmatchings/src/act", BeforeFunc);
INCLUDE_ASM("asm/nonmatchings/src/act", ACTDebugMove);
void actInitialize_geo(void) {}
INCLUDE_ASM("asm/nonmatchings/src/act", ACTReserveTarget);
extern void iosThreadSleep(void);

void _ACTRun(int n) {
    int i;
    if (n == 0) {
        for (;;) {
            iosThreadSleep();
        }
    }
    if (n > 0) {
        i = n;
        do {
            iosThreadSleep();
            i--;
        } while (i != 0);
    }
}
extern int D_0028F4C0[];

void _ACTWait(int a0) {
    int count = (a0 * ((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1])) / 0x3C;
    if (a0 != 0) {
        if (count == 0) {
            count = 1;
        }
    }
    if (count == 0) {
        for (;;) {
            iosThreadSleep();
        }
    }
    if (count > 0) {
        int i = count;
        do {
            iosThreadSleep();
            i--;
        } while (i != 0);
    }
}
extern int isysGObjProcAddGOppArg();

void actCreateSubThreadGOppArg(int a0, int a1)
{
    *(int *)((char *)isysGObjProcAddGOppArg(D_0063A61C, a0, 0, a1) + 0x64) = 1;
}
void actSetInterrupt(char *self, int val) {
    *(int *)(self + 0x0) = val;
}
extern int matrixptr;
extern void sceVu0ApplyMatrix(void *a0, void *a1, void *a2);
extern void sceVu0TransposeMatrix(void *a0, void *a1);

void ConvertStickToAbsCoord(void *a0, float *a1) {
    Vec4 v = {{ a1[3], 0.0f, -a1[4], 0.0f }};
    float m[16];
    sceVu0TransposeMatrix(m, (void *)(matrixptr + 0x80));
    sceVu0ApplyMatrix(a0, m, &v);
}
void ActSetStartBrainStatus(char *self, int status)
{
    char *brain = *(char **)(self + 0x164);
    if (brain != 0) {
        *(int *)(brain + 0x448) = status;
    }
}
void actWaitCondition(int a0, int a1) {
    int t = a0 & a1;
    if (t == 0) {
        do {
            int count = (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] / 0x3C;
            int n = 1;
            if (count != 0) {
                n = count;
            }
            if (n == 0) {
                for (;;) {
                    iosThreadSleep();
                }
            }
            if (n > 0) {
                int i = n;
                do {
                    iosThreadSleep();
                    i--;
                } while (i != 0);
            }
        } while (t == 0);
    }
}
