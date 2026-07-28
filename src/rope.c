#include "common.h"

void InitRopeGeo(void) {}

INCLUDE_ASM("asm/nonmatchings/src/rope", SetRopeFixPoint);

INCLUDE_ASM("asm/nonmatchings/src/rope", HoldRope);

INCLUDE_ASM("asm/nonmatchings/src/rope", ropeGeo);

INCLUDE_ASM("asm/nonmatchings/src/rope", RopeDL);

INCLUDE_ASM("asm/nonmatchings/src/rope", CheckRopeUpperWallClimbable);

INCLUDE_ASM("asm/nonmatchings/src/rope", ReleaseRope);

