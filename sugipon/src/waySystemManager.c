#include "common.h"

extern void playSEConditionID(int a0, int a1);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/waySystemManager", CreateWaySystemManagerGObj);

extern int func_0023D3C0(int a, int b, int c, int d, int e, int f, int g);
extern void func_001EF360(void);
extern int D_0062BA28;

int RequestGetWayBegin(void) {
    int v = func_0023D3C0(0, 0, 0, 0, (int)&func_001EF360, 0, 0);
    D_0062BA28 = v;
    return v;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/waySystemManager", actWaySystemCore);

extern int GetNearNigePointN(int a, int b, int c, int d);

void func_001EF310(volatile unsigned int self)
{
    volatile int local;
    int *s = (int *)((int *)self)[0x20 / 4];
    int v;
    v = GetNearNigePointN((int)((char *)s + 0x10), (int)((char *)s + 0x20), (int)((char *)s + 0xA0), 1);
    s[0x4 / 4] = v;
    s[0] = 1;
    s[0xB0 / 4] = 0;
}

extern void _ACTWait(int a0);
void func_001EF360(void) {
    for (;;) {
        _ACTWait(1);
    }
}

void func_001EF378(int a0) {
    playSEConditionID(a0, 0x40);
}

extern void ExecFrameDependSequence(int a0);

void func_001EF380(int a0) {
    ExecFrameDependSequence(a0);
    playSEConditionID(a0, 0x41);
}

void func_001EF3B0(int a0) {
    playSEConditionID(a0, 0x42);
}

void func_001EF3B8(int a0) {
    playSEConditionID(a0, 0x57);
}

void func_001EF3C0(int a0) {
    playSEConditionID(a0, 0x58);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/waySystemManager", func_001EF3C8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/waySystemManager", func_001EF4F0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/waySystemManager", func_001EF8E8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/waySystemManager", func_001EFAF8);
