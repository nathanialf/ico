#include "common.h"


extern void func_0010ECB8();
INCLUDE_ASM("asm/nonmatchings/src/moveColTest", MoveColTestGeo);

INCLUDE_ASM("asm/nonmatchings/src/moveColTest", MoveColTestDL);

void InitMoveColTestGeo(int a0, int a1, int a2, int a3)
{
    func_0010ECB8(a0, a1, a2, a3);
}

INCLUDE_ASM("asm/nonmatchings/src/moveColTest", func_001E6968);

