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

void *GetGObjId(int *a0, int a1, int a2) {
    unsigned long long v = (unsigned int)a1;
    unsigned long long packed = ((unsigned long long)a2 << 32) | v;
    a0[0] = (int)v;
    a0[1] = (int)(packed >> 32);
    a0[2] = 0x52;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

void *PrintGObjID(char *a0, unsigned int a1) {
    unsigned long long v = (unsigned int)a1;
    *(int *)(a0 + 8) = 0x53;
    *(int *)(a0 + 0) = (int)v;
    *(int *)(a0 + 4) = (int)(v >> 32);
    *(int *)(a0 + 0xC) = 0;
    return a0 + 0x10;
}

void InitCameraGObjs(int a0)
{
    debug_assertMessage(D_0061C6B8, a0);
}

extern void func_00264128(void *dst, void *src, int count);

int CreateGObj(char *a0, int a1, char *a2, int a3, char *a4, int a5, char *a6, int a7) {
    int b = a5 + a7;
    if (a1 + a3 < b) {
        return 0;
    }
    if (a5 >= a1) {
        func_00264128(a0, a4, a1);
        func_00264128(a2, a4 + a1, a5 - a1);
        func_00264128(a2 + a5 - a1, a6, a7);
    } else if (a7 >= a1 - a5) {
        func_00264128(a0, a4, a5);
        func_00264128(a0 + a5, a6, a1 - a5);
        func_00264128(a2, a6 + a1 - a5, a7 - (a1 - a5));
    } else {
        func_00264128(a0, a4, a5);
        func_00264128(a0 + a5, a6, a7);
    }
    return b;
}

extern void func_00240950(int a0);

void CreateGObjByFuncSet(int *a0) {
    func_00240950(a0[0]);
    func_00240950(a0[1]);
    func_00240950(a0[20]);
}

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

