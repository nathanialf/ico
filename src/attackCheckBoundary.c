#include "common.h"




extern void playSEConditionID(int a0, int a1);
extern void _ACTWait();
extern int actInitialize();
extern void actInitialize_ext_charcter();
extern int AP1BeforeFunc();
INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", AttackCheckBoundaryBeforeFunc);

int InitAttackCheckBoundaryManagerGeo(int a0)
{
    return AP1BeforeFunc(a0, 0) ? 0 : -1;
}

int AttackCheckBoundaryManagerGeo(int a0)
{
    return AP1BeforeFunc(a0, 0) ? 0 : -1;
}

void AttackCheckBoundaryManagerDL(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", InitAttackCheckBoundaryGeo);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", AttackCheckBoundaryGeo);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", AttackCheckBoundaryDL);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", actAttackCheckBoundaryStart);

void GetAttackCheckBoundaryRadius(void) {}

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", CreateAttackCheckBoundary);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", GetAttackCheckBoundaryManagerStatus);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", switchOnSE);

void switchReleaseSE(int *self)
{
    int *p = actInitialize(self);
    long long v;
    actInitialize_ext_charcter(self);
    _ACTWait(1);
    v = *(long long *)((char *)p + 0x18);
    v |= 1LL << 32;
    *(long long *)((char *)p + 0x18) = v;
}

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BBFD0);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BBFE0);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BC088);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BC098);

void func_001BC0A8(int a0)
{
    playSEConditionID(a0, 0x3D);
}

void func_001BC0B0(int a0)
{
    playSEConditionID(a0, 0x3E);
}

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BC0B8);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BC130);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BC1A8);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BC438);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BC4B8);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BC530);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BC7F0);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BC870);

void func_001BC9A0(int a0)
{
    playSEConditionID(a0, 0x2);
}

void func_001BC9A8(int a0)
{
    playSEConditionID(a0, 0x24);
}

void func_001BC9B0(int a0)
{
    playSEConditionID(a0, 0x4);
}

void func_001BC9B8(int a0)
{
    playSEConditionID(a0, 0xD);
}

void func_001BC9C0(int a0)
{
    playSEConditionID(a0, 0x1E);
}

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BC9C8);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BCAF0);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BCC18);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BD138);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BD278);

