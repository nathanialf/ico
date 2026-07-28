#include "common.h"



extern void ExecFrameDependSequence(int a0);
extern void playSEConditionID(int a0, int a1);
extern int GetNearNigePointN();
INCLUDE_ASM("asm/nonmatchings/src/waySystemManager", CreateWaySystemManagerGObj);

INCLUDE_ASM("asm/nonmatchings/src/waySystemManager", RequestGetWayBegin);

INCLUDE_ASM("asm/nonmatchings/src/waySystemManager", actWaySystemCore);

void func_001F2320(volatile unsigned int self)
{
    volatile int local;
    int *s = (int *)((int *)self)[0x20 / 4];
    int v;
    v = GetNearNigePointN((int)((char *)s + 0x10), (int)((char *)s + 0x20), (int)((char *)s + 0xA0), 1);
    s[0x4 / 4] = v;
    s[0] = 1;
    s[0xB0 / 4] = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/waySystemManager", func_001F2370);

INCLUDE_ASM("asm/nonmatchings/src/waySystemManager", func_001F2388);

void func_001F2390(int a0)
{
    ExecFrameDependSequence(a0);
    playSEConditionID(a0, 0x41);
}

void func_001F23C0(int a0)
{
    playSEConditionID(a0, 0x42);
}

void func_001F23C8(int a0)
{
    playSEConditionID(a0, 0x57);
}

void func_001F23D0(int a0)
{
    playSEConditionID(a0, 0x58);
}

INCLUDE_ASM("asm/nonmatchings/src/waySystemManager", func_001F23D8);

INCLUDE_ASM("asm/nonmatchings/src/waySystemManager", func_001F2500);

INCLUDE_ASM("asm/nonmatchings/src/waySystemManager", func_001F28F8);

INCLUDE_ASM("asm/nonmatchings/src/waySystemManager", func_001F2B08);

