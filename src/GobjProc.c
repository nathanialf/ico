#include "common.h"




extern void func_00100560();
extern void func_00100540();
extern void iosMallocCheckLeak2();
extern int D_0061C6B8[];
extern void debug_assertMessage(char *fmt, ...);
INCLUDE_ASM("asm/nonmatchings/src/GobjProc", ResetGObjProc);

int *GetMaxGObj(int *a0, long long a1, long long a2, long long a3)
{
    long long t = (a3 << 56) | (a2 << 48) | (a1 << 32);
    a0[1] = (int)(t >> 32);
    a0[2] = 0x50;
    a0[0] = 0;
    a0[3] = 0;
    return a0 + 4;
}

int *GetGObjP(int *a0, long long a1, long long a2, long long a3)
{
    long long t = (a1 << (27 + 32)) | (a3 << 48) | (a2 << 32);
    a0[1] = (int)(t >> 32);
    a0[2] = 0x51;
    a0[0] = 0;
    a0[3] = 0;
    return a0 + 4;
}

INCLUDE_ASM("asm/nonmatchings/src/GobjProc", GetGObjId);

INCLUDE_ASM("asm/nonmatchings/src/GobjProc", PrintGObjID);

void InitCameraGObjs(int a0)
{
    debug_assertMessage(D_0061C6B8, a0);
}

INCLUDE_ASM("asm/nonmatchings/src/GobjProc", CreateGObj);

INCLUDE_ASM("asm/nonmatchings/src/GobjProc", CreateGObjByFuncSet);

INCLUDE_ASM("asm/nonmatchings/src/GobjProc", func_0023F960);

INCLUDE_ASM("asm/nonmatchings/src/GobjProc", func_0023FB20);

INCLUDE_ASM("asm/nonmatchings/src/GobjProc", func_0023FCB8);

INCLUDE_ASM("asm/nonmatchings/src/GobjProc", func_0023FDA0);

INCLUDE_ASM("asm/nonmatchings/src/GobjProc", func_0023FDF0);

INCLUDE_ASM("asm/nonmatchings/src/GobjProc", func_00240090);

INCLUDE_ASM("asm/nonmatchings/src/GobjProc", func_00240218);

INCLUDE_ASM("asm/nonmatchings/src/GobjProc", func_00240600);

INCLUDE_ASM("asm/nonmatchings/src/GobjProc", func_00240650);

INCLUDE_ASM("asm/nonmatchings/src/GobjProc", func_002407C0);

void func_00240950(int a0)
{
    iosMallocCheckLeak2(a0 & 0x0FFFFFFF);
}

INCLUDE_ASM("asm/nonmatchings/src/GobjProc", func_00240960);

int func_00240A20(int *self)
{
    int ret;
    func_00100560(self[0x40 / 4]);
    ret = (self[0x10 / 4] << 11) + self[0x14 / 4];
    func_00100540(self[0x40 / 4]);
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/src/GobjProc", func_00240A70);

