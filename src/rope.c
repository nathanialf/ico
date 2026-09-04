#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/rope", InitRopeGeo);
INCLUDE_ASM("asm/nonmatchings/src/rope", SetRopeFixPoint);
INCLUDE_ASM("asm/nonmatchings/src/rope", HoldRope);
INCLUDE_ASM("asm/nonmatchings/src/rope", ropeGeo);
INCLUDE_ASM("asm/nonmatchings/src/rope", RopeDL);
int CheckRopeUpperWallClimbable(int a0, char *a1) {
    return *(int *)(*(char **)(*(char **)(a1 + 0x15C) + 0x830) + 4);
}
void ReleaseRope(void) {}
INCLUDE_ASM("asm/nonmatchings/src/rope", RopeGeo);
