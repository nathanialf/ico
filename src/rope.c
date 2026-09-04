#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/rope", InitRopeGeo);
INCLUDE_ASM("asm/nonmatchings/src/rope", SetRopeFixPoint);
INCLUDE_ASM("asm/nonmatchings/src/rope", HoldRope);
INCLUDE_ASM("asm/nonmatchings/src/rope", ropeGeo);
INCLUDE_ASM("asm/nonmatchings/src/rope", RopeDL);
INCLUDE_ASM("asm/nonmatchings/src/rope", CheckRopeUpperWallClimbable);
void ReleaseRope(void) {}
INCLUDE_ASM("asm/nonmatchings/src/rope", RopeGeo);
