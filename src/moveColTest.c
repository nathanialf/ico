#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/moveColTest", MoveColTestGeo);
extern void p2o_DispVU1();

void MoveColTestDL(int a0, int a1, int a2, int a3)
{
    p2o_DispVU1(a0, a1, a2, a3);
}
INCLUDE_ASM("asm/nonmatchings/src/moveColTest", InitMoveColTestGeo);
